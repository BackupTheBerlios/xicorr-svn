################################################################################
# Automatically-generated file. Do not edit!
################################################################################

ROOT := ..

-include $(ROOT)/makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include $(SUBDIRS:%=%/subdir.mk)
-include objects.mk
-include $(DEPS)
-include $(ROOT)/makefile.defs

all: libxicor_xsystem.so

dependents:
	-cd /home/burivuh/workspace/xicor/xicor_base/Debug && $(MAKE) all
	-cd /home/burivuh/workspace/xicor/xicor_xlib/Debug && $(MAKE) all

libxicor_xsystem.so: $(OBJS) /home/burivuh/workspace/xicor/xicor_base/Debug/libxicor_base.so /home/burivuh/workspace/xicor/xicor_xlib/Debug/libxicor_xlib.so
	@echo 'Building target: $@'
	g++ -L../../xicor_xlib/Debug -shared -o $@ $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building: $@'

clean:
	-$(RM) $(OBJS) $(DEPS) libxicor_xsystem.so

.PHONY: all clean dependents
/home/burivuh/workspace/xicor/xicor_base/Debug/libxicor_base.so:
/home/burivuh/workspace/xicor/xicor_xlib/Debug/libxicor_xlib.so:

-include $(ROOT)/makefile.targets
