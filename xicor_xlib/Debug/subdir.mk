################################################################################
# Automatically-generated file. Do not edit!
################################################################################

S_UPPER_SRCS += \
${addprefix $(ROOT)/, \
}

CPP_SRCS += \
${addprefix $(ROOT)/, \
xicor_xlib.cpp \
}

CC_SRCS += \
${addprefix $(ROOT)/, \
}

C_SRCS += \
${addprefix $(ROOT)/, \
}

C_UPPER_SRCS += \
${addprefix $(ROOT)/, \
}

CXX_SRCS += \
${addprefix $(ROOT)/, \
}

S_SRCS += \
${addprefix $(ROOT)/, \
}

# Each subdirectory must supply rules for building sources it contributes
%.o: $(ROOT)/%.cpp
	@echo 'Building file: $<'
	@echo g++ -I../../xicor_base -I.. -O0 -g3 -pedantic -pedantic-errors -Wall -Werror -c -fmessage-length=0 -o$@ $<
	@g++ -I../../xicor_base -I.. -O0 -g3 -pedantic -pedantic-errors -Wall -Werror -c -fmessage-length=0 -o$@ $< && \
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	g++ -MM -MG -P -w -I../../xicor_base -I.. -O0 -g3 -pedantic -pedantic-errors -Wall -Werror -c -fmessage-length=0  $< >> $(@:%.o=%.d)
	@echo 'Finished building: $<'
	@echo ' '


