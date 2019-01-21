# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendRecentItems(usersTimestamp, itemsTimestamp, usersTargets, globalSettings, outputFileName):

	# variables
	lastConsumption = {}
	recentItems = {}
	recommendations = []
	
	# Ranking of items sorted by last consumption
	for i in itemsTimestamp.keys():
		# save the max time of consumption
		lastConsumption[i] = max(itemsTimestamp[i].iteritems(), key=operator.itemgetter(1))[1]
		
	# Sorted descending
	recentItems = OrderedDict(sorted(lastConsumption.items(), key=operator.itemgetter(1), reverse=True))
	recommendations = recentItems.keys()
	
	with open(outputFileName, 'w') as outputFile:
		spamwriter = csv.writer(outputFile, delimiter='\t', quoting = csv.QUOTE_NONE)
		# retrieve the top K maxCoverage items not consumed by user
		cont = 1
		issuedItems = ""
		# for each item
		for i in recommendations:
			# select just k items
			if (cont <= int(globalSettings['recommendation_size'])):
				issuedItems += str(i) + ":" + str(0.0) + " "
				cont += 1
			else:
				break
		# for each user
		for u in usersTargets:
			recommendationItems = str(u) + " " + issuedItems
			spamwriter.writerow([recommendationItems])

	outputFile.close()
