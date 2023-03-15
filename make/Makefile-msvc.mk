#compiler
CXX = cl
WARS += /wd 4715
LNKS += /IGNORE:4099
LIBS += opengl32.lib glu32.lib
QLIB = C:\Qt\6.4.2\msvc2019_64\lib
QINC = C:\Qt\6.4.2\msvc2019_64\include
DEFS += /D "NOMINMAX" /D "_USE_MATH_DEFINES"
INCS += /I inc /I build/windows /I ..\external\cpp\inc
DEFS += -D QT_CORE_LIB -D QT_GUI_LIB -D QT_WIDGETS_LIB -D QT_SHARED -D QT_OPENGL_LIB -D QT_CONSOLE -D QT_PRINTSUPPORT_LIB
INCS += /I $(QINC) /I $(QINC)\QtCore /I $(QINC)\QtGui /I $(QINC)\QtWidgets /I $(QINC)\QtOpenGL /I $(QINC)\QtOpenGLWidgets
CXXFLAGS = /nologo /std:c++20 /Zc:__cplusplus /EHsc /c /openmp /diagnostics:caret $(DEFS) $(INCS) $(WARS)

LIBS +=\
	$(QLIB)/Qt6Gui.lib\
	$(QLIB)/Qt6Core.lib\
	$(QLIB)/Qt6OpenGL.lib\
	$(QLIB)/Qt6Widgets.lib\
	$(QLIB)/Qt6PrintSupport.lib\
	$(QLIB)/Qt6OpenGLWidgets.lib

DLLS =

#mode
ifneq ($(m), r)
	mode = debug
	LNKS += /debug
	CXXFLAGS += /Zi /FS
	CXXFLAGS += /D "_DEBUG" /Od /MDd /RTC1
	CXXFLAGS += /Fddist/windows/$(mode)/plate.pdb
else
	mode = release
	CXXFLAGS += /D "NDEBUG" /O2 /MD
endif

#ouput
out = dist/windows/$(mode)/plate.exe

#interfaces
dir := $(shell cd)
uif := $(subst \,/,$(subst $(dir)\,,$(shell dir ui /s /b /a-d)))

#headers
hea := $(subst \,/,$(subst $(dir)\,,$(shell dir inc /s /b /a-d)))

#sources
src := $(subst \,/,$(subst $(dir)\,,$(shell dir src /s /b /a-d)))

#qt files
uig := $(subst ui/,build/windows/uic/,$(subst .ui,.h,$(uif)))
mog := $(subst inc/,build/windows/moc/,$(subst .h,.cpp,$(hea)))

#objects
obj := $(subst src/,build/windows/$(mode)/obj/,$(subst .cpp,.o,$(src)))
obj += $(subst build/windows/moc/,build/windows/$(mode)/moc/,$(subst .cpp,.o,$(mog)))

#dependencies
dep := $(subst .o,.d, $(obj))

#rules
all : $(out)
	@echo build($(mode)): complete!

run : $(out)
	@./$(out)

debug :
	@devenv /debugexe $(out)

setup :
	@if not exist dist\windows\$(mode) mkdir dist\windows\$(mode)

$(out) : setup $(uig) $(mog) $(obj) $(DLLS)
	@echo executable($(mode)): $@
	@link /nologo $(LNKS) /out:$(out) $(obj) $(LIBS)

build/windows/moc/%.cpp: inc/%.h
	@echo mocing($(mode)): $<
	@if exist $(subst /,\,$@) del $(subst /,\,$@)
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@moc $< -o $@ -nw

build/windows/uic/%.h : ui/%.ui
	@echo uicing($(mode)): $<
	@if exist $(subst /,\,$@) del $(subst /,\,$@)
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@uic $< -o $@

build/windows/$(mode)/obj/%.o : src/%.cpp build/windows/$(mode)/obj/%.d
	@echo compiling($(mode)): $<
	@if exist $(subst /,\,$@) del $(subst /,\,$@)
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@$(CXX) $(CXXFLAGS) /Fo:$@ $<
	@python msvc-dep.py $< $@

build/windows/$(mode)/moc/%.o : build/windows/moc/%.cpp build/windows/$(mode)/moc/%.d
	@echo compiling($(mode)): $<
	@if exist $(subst /,\,$@) del $(subst /,\,$@)
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@$(CXX) $(CXXFLAGS) /Fo:$@ $< > nul
	@python msvc-dep.py $< $@

dist/windows/$(mode)/%.dll : ../external/cpp/dll/x64/%.dll
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@copy /y $(subst /,\,$<) $(subst /,\,$@) > nul

$(dep) : ;

-include $(dep)

clean :
	@if exist build\windows\uic rmdir /s /q build\windows\uic
	@if exist build\windows\moc rmdir /s /q build\windows\moc
	@if exist build\windows\rsc rmdir /s /q build\windows\rsc
	@if exist dist\windows\$(mode) rmdir /s /q dist\windows\$(mode)
	@if exist build\windows\$(mode) rmdir /s /q build\windows\$(mode)
	@echo clean($(mode)): complete!

print-% :
	@echo $* = $($*)

.PHONY : all run clean print-%