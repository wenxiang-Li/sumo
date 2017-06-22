#!/usr/bin/env python
"""
@file evacuation.py
@author  Martin Taraz
@author  Michael Behrisch
@date    2015-09-09
@version $Id$

Starts the creation of an Evacuation Scenario

Sources:
Inhabitant data
https://www.destatis.de/DE/ZahlenFakten/LaenderRegionen/Regionales/Gemeindeverzeichnis/Administrativ/Archiv/GVAuszugQ/AuszugGV3QAktuell.html
Gemeinde XML data generated by using the Shape Data
Source: https://www.zensus2011.de/SharedDocs/Downloads/DE/Shapefile/VG250_1Jan2011_WGS84.zip?__blob=publicationFile&v=29

SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
Copyright (C) 2009-2017 DLR (http://www.dlr.de/) and contributors

This file is part of SUMO.
SUMO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
"""
from __future__ import absolute_import
from __future__ import print_function

import os
import sys
import subprocess
import math
import csv

SUMO_HOME = os.environ.get("SUMO_HOME", os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
sys.path.append(os.path.join(SUMO_HOME, "tools"))

import xml.etree.cElementTree as ET
from xml.etree.ElementTree import Element, SubElement, Comment, tostring
from xml.dom import minidom
from shapely.geometry import Polygon

import osmBuild
import osmGet
import sumolib  # noqa

import generateTraffic


def mergePopulationData(populationFile, regionFile, mergedFile):
    csvReader = csv.reader(open(populationFile), delimiter=',', quotechar='"')
    inhabDict = {}
    for entry in csvReader:
        if csvReader.line_num <= 3:
            continue
        while(len(entry[0]) < 2):
            entry[0] = '0' + entry[0]
        while(len(entry[2]) < 2):
            entry[2] = '0' + entry[2]
        while(len(entry[3]) < 4):
            entry[3] = '0' + entry[3]
        while(len(entry[4]) < 3):
            entry[4] = '0' + entry[4]
        inhabDict["".join(entry[:5])] = str(entry[6]).replace(' ', '')

    root = ET.ElementTree(file=regionFile).getroot()
    for parents in root.findall("./*"):
        for elem in parents.findall("param[7]"):
            RSValue = str(elem.attrib)[11:23]
            inhabitants = SubElement(parents, 'param')
            if RSValue in inhabDict:
                inhabitants.clear()
                inhabitants.attrib = {
                    'key': "INHABITANTS", 'value': inhabDict[RSValue]}
    outstr = minidom.parseString(ET.tostring(root)).toprettyxml(indent="    ")
    with open(mergedFile, 'w') as out:
        out.write(outstr.encode('utf-8'))


def extract(mergedPopulationFile, mappedSiteFile, intersectionFile):
    PopulationXML = ET.ElementTree(file=mergedPopulationFile)
    EvacuationXML = ET.ElementTree(file=mappedSiteFile)
    PopRoot = PopulationXML.getroot()
    EvaRoot = EvacuationXML.getroot()
    Schnittmenge = []
    for evaArea in EvaRoot.findall("./poly[0]"):
        koordinatenStr = evaArea.attrib["shape"]
        koordinatenList = [tuple(map(float, x.split(',')))
                           for x in koordinatenStr.split()]
        evacuationArea = Polygon(koordinatenList)

    for PopArea in PopRoot.findall("./poly"):
        koordinatenStr = PopArea.attrib["shape"]
        koordinatenList = [tuple(map(float, x.split(',')))
                           for x in koordinatenStr.split()]
        Gemeinde = Polygon(koordinatenList)
        if Gemeinde.intersection(evacuationArea):
            for Inhab in PopArea.findall("./param"):
                if Inhab.attrib["key"] == "INHABITANTS":
                    Einwohner = int((Inhab.attrib["value"]))
                    Einwohner *= Gemeinde.intersection(
                        evacuationArea).area / Gemeinde.area
                    Einwohner = str(Einwohner)
                    Schnittmenge.append(
                        (Gemeinde.intersection(evacuationArea), Einwohner))
                    print("merge!")

    root = ET.Element('additional')
    outTree = ET.ElementTree(root)
    i = 1
    for G in Schnittmenge:
        poly = ET.SubElement(root, 'poly')
        exterior = G[0].exterior.coords
        OutExterior = ''
        for elem in exterior:
            OutExterior += str(elem[0]) + "," + str(elem[1]) + " "
        identity = "Schnittflache" + str(i)
        poly.attrib = {
            "id": identity, "shape": OutExterior, "inhabitants": G[1]}
        i += 1
    outstr = minidom.parseString(ET.tostring(root)).toprettyxml(indent="   ")
    with open(intersectionFile, 'w') as out:
        out.write(outstr)


def buildEvaSite(inputFile, siteFile):
    dots = 10
    with open(siteFile, 'w') as out:
        out.write("<additional>\n")
        for poi in sumolib.output.parse(inputFile, "poi"):
            lon = float(poi.lon)
            lat = float(poi.lat)
            radius = float(poi.radius) * 360 / 4008 / 1000
            shape = ""
            if poi.color is None:
                poi.color = "0,0,255"
            for i in range(dots):
                angle = 2 * math.pi * i / dots
                templon = lon + radius * math.cos(angle)
                templat = lat + radius * \
                    math.sin(angle) * math.cos(math.radians(lat))
                shape += "%s,%s " % (templon, templat)
            out.write('    <poly id="%s" color="%s" fill="1" layer="-1" shape="%s"/>\n' %
                      (poi.id, poi.color, shape[:-1]))
        out.write("</additional>\n")


print("building Evacuation Site")
prefix = "evacuationArea"
siteFile = "site.poly.xml"
mappedSiteFile = "mappedSite.poly.xml"
mergedPopulationFile = "population.poly.xml"
intersectionFile = "intersections.poly.xml"
if len(sys.argv) > 1:
    buildEvaSite(sys.argv[1], siteFile)
else:
    buildEvaSite("inputLocations.poi.xml", siteFile)
print("osm Get")
osmGet.get(["-x", siteFile])
print("osm Build")
osmOptions = ['-f', 'osm_bbox.osm.xml', '-p', prefix, '--vehicle-classes', 'road',
              '-m', os.path.join(SUMO_HOME, 'data', 'typemap', 'osmPolyconvert.typ.xml')]
osmBuild.build(osmOptions)
print("polyconvert")
sys.stdout.flush()
subprocess.call([sumolib.checkBinary('polyconvert'), '-n', '%s.net.xml' %
                 prefix, '--xml-files', siteFile, '-o', mappedSiteFile])
print("merging")
mergePopulationData("population.csv", 'regions.poly.xml', mergedPopulationFile)
print("extracting population data")
extract(mergedPopulationFile, mappedSiteFile, intersectionFile)
print("generating traffic")
generateTraffic.generate(
    '%s.net.xml' % prefix, mappedSiteFile, intersectionFile, '%s.rou.xml' % prefix)
print("calling sumo")
sys.stdout.flush()
sumo = sumolib.checkBinary('sumo')
sumoOptions = [sumo, '-n', "%s.net.xml" % prefix, '-a', "%s.poly.xml,inputLocations.poi.xml,%s" % (prefix, mappedSiteFile),
               '-r', '%s.rou.xml' % prefix, '--ignore-route-errors', '--no-step-log', '--save-configuration', '%s.sumocfg' % prefix]
subprocess.call(sumoOptions)
subprocess.call([sumo, '%s.sumocfg' % prefix])
#subprocess.call([sumolib.checkBinary('sumo-gui'), '%s.sumocfg' % prefix])
print("done")
