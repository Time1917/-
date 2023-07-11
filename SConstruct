import os
import sys
import rtconfig

if os.getenv('RTT_ROOT'):
#    RTT_ROOT = os.getenv('RTT_ROOT')
	RTT_ROOT = os.path.normpath(os.getcwd() + '/../..')
else:
    RTT_ROOT = os.path.normpath(os.getcwd() + '/../..')

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
from building import *

TARGET = 'rtthread.' + rtconfig.TARGET_EXT

env = Environment(tools = ['mingw'],
	AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
	CC = rtconfig.CC, CCFLAGS = rtconfig.CFLAGS,
	AR = rtconfig.AR, ARFLAGS = '-rc',
	LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS)
env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

Export('RTT_ROOT')
Export('rtconfig')

# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT)
    
#if GetDepend('RT_USING_RTGUI'):
    #objs = objs + SConscript(RTT_ROOT + '/examples/gui/SConscript', variant_dir='build/examples/gui', duplicate=0)
    
# make a building
DoBuilding(TARGET, objs)