# -*- coding: utf-8 -*-
"""
Created on Thu May  9 09:36:27 2019

@author: Ghiordy F. Contreras
"""

import math

def volumetricFlowRate(v,r):
    """ all units in SI to correct computing """
    return [round(math.pi*(r**2)*v,4),
            ' full:',math.pi*(r**2)*v]

def dQdP(V,Q,I):
    result = [0,0]
    result[0] = Q[0]/(V*I[0])
    result[0] = result[0]*((Q[1]/Q[0])+((V*I[1])/(V*I[0])))
    return [[result],[round(result[0],4),round(result[1],4)]]
    
