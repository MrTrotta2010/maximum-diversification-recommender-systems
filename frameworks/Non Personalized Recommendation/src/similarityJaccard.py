# -*- coding: utf-8 -*-

import commands
import operator
import os
import sys
import ConfigParser

##########################################################################################################################################
def jaccard_similarity(x,y):
	# users set of item x
	setItemX = numpy.nonzero(x)
	setItemX = numpy.array(setItemX)[0]
	# users set of item y	
	setItemY = numpy.nonzero(y)
	setItemY = numpy.array(setItemY)[0]

	intersection_cardinality = len(set.intersection(*[set(setItemX), set(setItemY)]))
	union_cardinality = len(set.union(*[set(setItemX), set(setItemY)]))

	if (union_cardinality == 0):
		return 1
	else:
		return intersection_cardinality/float(union_cardinality)

##########################################################################################################################################
