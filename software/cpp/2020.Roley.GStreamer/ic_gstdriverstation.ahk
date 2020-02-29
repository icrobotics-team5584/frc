; NOTE: you can use ALT+F4 to close selected windows that have no title bar!
;
; NOTE: we use this order as the height, width and location of componets have dependencies ...
;
;         FRC DRIVER STATION (WIN ID = 1)
;         GSTREAMER PORT 1181 (WIN ID = 3) depends on height of ID1
;         GSTREAMER PORT 1182 (WIN ID = 4) depends on width of ID3
;         GSTREAMER PORT 1183 (WIN ID = 5) depends on width of ID3 and ID4
;         FRC SHUFFLE BOARD (WIN ID = 2) depends on width of ID3 and height of ID1 and ID4

; NEW APPROACH . . . 
;
;         STEP 1: LETS LAUNCH EVERYTHING 
;         STEP 2: LOOP FOR 60 SECONDS REPEATING WINMOVE AND WINSET TO FORCE ALL WINDOWS TO CORRECT POSITIONS AND SIZES


; FRC DRIVER STATION

if not WinExist("ahk_exe DriverStation.exe")
    Run, "C:\Program Files (x86)\FRC Driver Station\DriverStation.exe"

; FRC SHUFFLE BOARD (WIN ID = 2)

if not WinExist("ahk_exe javaw.exe")
    Run, "C:\Users\Public\wpilib\2020\tools\shuffleboard.vbs"

; GSTREAMER PORT 1181 (WIN ID = 3)

if not WinExist("ahk_exe gst-launch-1.0.1181.exe")
    Run, "C:\scm\icrobotics\frc\software\cpp\2020.Roley.GStreamer\ic_gstclient_1181.bat", , Hide

; GSTREAMER PORT 1182 (WIN ID = 4)

if not WinExist("ahk_exe gst-launch-1.0.1182.exe")
    Run, "C:\scm\icrobotics\frc\software\cpp\2020.Roley.GStreamer\ic_gstclient_1182.bat", , Hide

; GSTREAMER PORT 1183 (WIN ID = 5)

if not WinExist("ahk_exe gst-launch-1.0.1183.exe")
    Run, "C:\scm\icrobotics\frc\software\cpp\2020.Roley.GStreamer\ic_gstclient_1183.bat", , Hide

Loop, 30
{
    ; FRC DRIVER STATION (WIN ID = 1)

    WinActivate, ahk_exe DriverStation.exe
    WinGet, Win_ID1, , ahk_exe DriverStation.exe
    WinRestore, ahk_id %Win_ID1%
    WinSet, Style, -0xC40000, ahk_id %Win_ID1%
    WinGet, Win_Status1, MinMax, ahk_id %Win_ID1%
    WinGetPos, Win_X1, Win_Y1, Win_Width1, Win_Height1, ahk_id %Win_ID1%
    NewWin_X1 := 0
    NewWin_Y1 := A_ScreenHeight - Win_Height1
    NewWin_Width1 := A_ScreenWidth
    NewWin_Height1 := Win_Height1
    If (%Win_Status1% = 0)
        WinRestore, ahk_id %Win_ID1%
    WinMove, ahk_id %Win_ID1%, , %NewWin_X1%, %NewWin_Y1%, %NewWin_Width1%, %NewWin_Height1%

    ; GSTREAMER PORT 1181 (WIN ID = 3)

    WinActivate, ahk_exe gst-launch-1.0.1181.exe
    WinGet, Win_ID3, , ahk_exe gst-launch-1.0.1181.exe
    WinRestore, ahk_id %Win_ID3%
    WinSet, Style, -0xC40000, ahk_id %Win_ID3%
    WinGet, Win_Status3, MinMax, ahk_id %Win_ID3%
    WinGetPos, Win_X3, Win_Y3, Win_Width3, Win_Height3, ahk_id %Win_ID3%
    NewWin_X3 := 0
    NewWin_Y3 := 0
    NewWin_Height3 := A_ScreenHeight - Win_Height1
    NewWin_Width3 := Round(NewWin_Height3*640/480)
    If (%Win_Status3% = 0)
        WinRestore, ahk_id %Win_ID3%
    WinMove, ahk_id %Win_ID3%, , %NewWin_X3%, %NewWin_Y3%, %NewWin_Width3%, %NewWin_Height3%

    ; GSTREAMER CHANNEL PORT 1182 (WIN ID = 4)

    WinActivate, ahk_exe gst-launch-1.0.1182.exe
    WinGet, Win_ID4, , ahk_exe gst-launch-1.0.1182.exe
    WinRestore, ahk_id %Win_ID4%
    WinSet, Style, -0xC40000, ahk_id %Win_ID4%
    WinGet, Win_Status3, MinMax, ahk_id %Win_ID4%
    WinGetPos, Win_X4, Win_Y4, Win_Width4, Win_Height4, ahk_id %Win_ID4%
    NewWin_X4 := NewWin_Width3
    NewWin_Y4 := 0
    NewWin_Width4 := Round((A_ScreenWidth-NewWin_Width3)/2)
    NewWin_Height4 := Round(NewWin_Width4*480/640)
    If (%Win_Status4% = 0)
        WinRestore, ahk_id %Win_ID4%
    WinMove, ahk_id %Win_ID4%, , %NewWin_X4%, %NewWin_Y4%, %NewWin_Width4%, %NewWin_Height4%

    ; GSTREAMER CHANNEL PORT 1183 (WIN ID = 5)

    WinActivate, ahk_exe gst-launch-1.0.1183.exe
    WinGet, Win_ID5, , ahk_exe gst-launch-1.0.1183.exe
    WinRestore, ahk_id %Win_ID5%
    WinSet, Style, -0xC40000, ahk_id %Win_ID5%
    WinGet, Win_Status5, MinMax, ahk_id %Win_ID5%
    WinGetPos, Win_X5, Win_Y5, Win_Width5, Win_Height5, ahk_id %Win_ID5%
    NewWin_X5 := NewWin_Width3 + NewWin_Width4
    NewWin_Y5 := 0
    NewWin_Width5 := A_ScreenWidth - NewWin_Width3 - NewWin_Width4
    NewWin_Height5 := Round(NewWin_Width5*480/640)
    If (%Win_Status5% = 0)
        WinRestore, ahk_id %Win_ID5%
    WinMove, ahk_id %Win_ID5%, , %NewWin_X5%, %NewWin_Y5%, %NewWin_Width5%, %NewWin_Height5%

    ; FRC SHUFFLE BOARD (WIN ID = 2)

    WinActivate, ahk_exe javaw.exe
    WinGet, Win_ID2, , ahk_exe javaw.exe
    WinRestore, ahk_id %Win_ID2%
    WinSet, Style, -0xC40000, ahk_id %Win_ID2%
    WinGet, Win_Status2, MinMax, ahk_id %Win_ID2%
    WinGetPos, Win_X2, Win_Y2, Win_Width2, Win_Height2, ahk_id %Win_ID2%
    NewWin_X2 := NewWin_Width3
    NewWin_Y2 := NewWin_Height4
    NewWin_Width2 := A_ScreenWidth - NewWin_Width3
    NewWin_Height2 := A_ScreenHeight - NewWin_Height1 - NewWin_Height4
    If (%Win_Status2% = 0)
        WinRestore, ahk_id %Win_ID2%
    WinMove, ahk_id %Win_ID2%, , %NewWin_X2%, %NewWin_Y2%, %NewWin_Width2%, %NewWin_Height2%

    Sleep 2000

}

Return
