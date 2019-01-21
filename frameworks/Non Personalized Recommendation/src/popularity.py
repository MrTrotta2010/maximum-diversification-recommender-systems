# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendPopularity(usersRatings, itemsRatings, usersTargets, globalSettings, outputFileName):

	# initialize variables
	users = len(usersRatings.keys())
	items = len(itemsRatings.keys())	
	popularity = {}
	sortPopularity = {}
	recommendations = []
		
	# for each itemId
	for i in itemsRatings.keys():
		# Popularity of an item is equal to the number of distinct users who consumed the item
		popularity[i] = len(itemsRatings[i].keys())
		
	# generate the ranking descending of populariy
	sortPopularity = OrderedDict(sorted(popularity.items(), key=operator.itemgetter(1), reverse=True))
	recommendations = sortPopularity.keys()
	
	## DUMP-RECOMMENDATIONS
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
