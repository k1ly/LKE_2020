@ECHO OFF
ml /Fo "C:\Users\��ਫ�\OneDrive\Documents\LP_KP\LKE-2020\CODE\Debug\CODE.obj"  /c "C:\Users\��ਫ�\OneDrive\Documents\LP_KP\LKE-2020\CODE\CODE.asm"
link /OPT:NOREF /DEBUG /OUT:"C:\Users\��ਫ�\OneDrive\Documents\LP_KP\LKE-2020\Debug\APP.exe" "C:\Users\��ਫ�\OneDrive\Documents\LP_KP\LKE-2020\CODE\Debug\CODE.obj" "C:\Users\��ਫ�\OneDrive\Documents\LP_KP\LKE-2020\Debug\STD.lib" "C:\Users\��ਫ�\OneDrive\Documents\LP_KP\LKE-2020\Debug\kernel32.lib" /SUBSYSTEM:CONSOLE
APP
