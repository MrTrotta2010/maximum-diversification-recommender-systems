# -*- coding: utf-8 -*-

import commands
import operator
import os
import sys
import ConfigParser
import time

pathname = os.path.dirname(sys.argv[0])
fullPath = os.path.abspath(pathname)

#sys.path.insert(1,fullPath + '/../recommendation/')

from io import *
from popularity import *
from randomPopularity import *
from topRated import *
from maxCoverage import *
from positiveFeedback_MaxCoverage import *
from restrictionsMaxCoverage import *
from retrievalRestrictionsMaxCoverage import *
from recentItems import *
from nicheCoverage import *
from nicheRelevantCoverage import *
from scipy.sparse import csr_matrix
from scipy.special import expit

##########################################################################################################################################

def main():
	#set global settings
	Config = ConfigParser.ConfigParser()
	Config.read(fullPath + "/../config.ini")
	globalSettings = ConfigSectionMap(Config, ["SectionZero","SectionOne"])
	
	(trainInput, testInput, clusterFileName, percentage, outputDirectory) = getArgs();
	
	#create output directory if it does not exist
	try:
		if not os.path.exists(outputDirectory):
			os.makedirs(outputDirectory)
	except:
		print str(sys.exc_info()[0])
		sys.exit(2)

	print "Loading input train data ..."
	# load setTrain data
	usersRatings, itemsRatings, usersTimestamp, itemsTimestamp = loadData(trainInput, globalSettings)
	usersTargets = loadTargets(testInput, globalSettings)
	print "Users: ",len(usersRatings.keys())
	print "Items: ",len(itemsRatings.keys())
	print "Users Targets: ",len(usersTargets)
	
	# generate recommendations
	print "Issuing recommendations ..."
	
	# run popularity
	print "- by popularity"
#	start_time = time.time()
#	recommendPopularity(usersRatings, itemsRatings, usersTargets, globalSettings, outputDirectory + 'finalRecommendations_Popularity.txt')
#	print("--TIME EXECUTION POPULARITY-- %s" % (time.time() - start_time))

	# run topRated
	print "- by topRated"
#	start_time = time.time()		
#	recommendTopRated(usersRatings, itemsRatings, usersTargets, globalSettings, outputDirectory + 'finalRecommendations_TopRated.txt')
#	print("--TIME EXECUTION topRated-- %s" % (time.time() - start_time))

	# run recentItems
	print "- by recentItems"
#	start_time = time.time()
#	recommendRecentItems(usersTimestamp, itemsTimestamp, usersTargets, globalSettings, outputDirectory + 'finalRecommendations_RecentItems.txt')
#	print("--TIME EXECUTION recentItems-- %s" % (time.time() - start_time))

	# run random Popularity
	print "- by randomPopularity"
#	start_time = time.time()
#	recommendRandomPopularity(usersRatings, itemsRatings, usersTargets, globalSettings, percentage, outputDirectory + 'finalRecommendations_RandomPopularity.txt')
#	print("--TIME EXECUTION randomPOPULARITY-- %s" % (time.time() - start_time))
	
	# run maxCoverage
	print "- by maxCoverage"
#	start_time = time.time()
#	recommendMaxCoverage(usersRatings, itemsRatings, usersTargets, globalSettings, outputDirectory + 'finalRecommendations_MaxCoverage.txt')
#	print("--TIME EXECUTION maxCoverage-- %s" % (time.time() - start_time))

	# run nicheRelevantCoverage
	print "- by niche Coverage with popularity concept"
#	start_time = time.time()
#	recommendNicheRelevantCoverage(clusterFileName, usersRatings, itemsRatings, usersTargets, globalSettings, outputDirectory + 'finalRecommendations_NicheRelevantCoverage.txt')
#	print("--TIME EXECUTION nicheCoverage-- %s" % (time.time() - start_time))

	# run nicheCoverage
	print "- by Niche-Coverage with user-coverage concept"
#	recommendNicheCoverage(clusterFileName, usersRatings, itemsRatings, usersTargets, globalSettings, outputDirectory + 'finalRecommendations_NicheCoverage.txt')
	
##########################################################################################################################################

def getArgs():
	try:
		opts, args = getopt.getopt(sys.argv[1:], "t:s:c:p:o:h")

	except:
		err = sys.exc_info()[0]
		print str(err)
		usage()
		sys.exit(2)

	trainSet = None
	testSet = None
	percentage = None
	outputDirectory = None
	clusterFileName = None
	
	for opt,arg in opts:
		if opt == "-t":
			trainSet = arg
		elif opt == "-s":
			testSet = arg
		elif opt == "-c":
			clusterFileName = arg
		elif opt == "-p":
			percentage = arg
		elif opt == "-o":
			outputDirectory = arg
		elif opt == "-h":
			usage()
		else:
			assert False, "Unknown option!"

	if( (trainSet == None) or (clusterFileName == None) or (outputDirectory == None) or (testSet == None) or (percentage == None)):
		print "\n\t***Error: Wrong number of parameters!";
		usage()
		sys.exit(2)
		
	return(trainSet, testSet, clusterFileName, percentage, outputDirectory)

##########################################################################################################################################

def usage():
	print "\n\tIn order to run this program, please, inform the following parameters:\n"
	print "\t\t-t Train Set Data File Name"
	print "\t\t-s Test Set Data File Name"
	print "\t\t-p Percentage of popular items" 
	print "\t\t\t\t 0.05 to ML-10M"
	print "\t\t\t\t 0. to Amazon-Clothes"
	print "\t\t\t\t 0. to Amazon-VideoGames"
	print "\t\t-o Ouput Directory Name"
	print "\t\t-h To print this help\n"
	
##########################################################################################################################################

if __name__ == '__main__':
        main()
