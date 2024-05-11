@echo off
REM ***********配置开始***********
REM 设置keil5可执行应用程序的路径
set UV=D:\Keil\UV4\UV4.exe
REM 设置keil项目路径,采用相对路径,所以请把此.bat脚本文件跟.uvprojx的项目文件放在同一个目录下
set UV_PRO_PATH=.\TouchGFX.uvprojx
REM 设置日志文件的路径
set LOG_PATH=.\TouchGFX\log.txt
REM ***********配置结束***********



echo        [1].Start building...

REM -b是编译,不用每次都重新编译,比较好,因为可以节省编译时间
REM -r不管之前的生成的中间文件存不存在,都重新编译, -j0是禁止打开keil5图形界面, -o是将编译信息输出到文件
%UV% -b %UV_PRO_PATH% -j0 -o %LOG_PATH% 

if %errorlevel%==0 (
REM	color 2f 这把背景改成绿色,字体颜色改成白色
REM	echo build completed,No Errors or Warnings
REM 如果没有错误和警告的话,则直接退出,啥也不显示
	echo        [2].Build ok, exit
	exit 0
)

REM 下面就是有错误或者警告了
if %errorlevel%==1 	(echo        [2].Warnings Only)
if %errorlevel%==2 	(echo        [2].Errors)
if %errorlevel%==3 	(echo        [2].Fatal Errors)
if %errorlevel%==11 (echo        [2].Cannot open project file to writing)
if %errorlevel%==12 (echo        [2].Device with given name no found on database)
if %errorlevel%==13 (echo        [2].Error writing project file)
if %errorlevel%==15 (echo        [2].Error reading import XML file)
if %errorlevel%==20 (echo        [2].Error converting project)

echo        [3].Build info as below:
REM type是把某个文件的内容显示出来
type %LOG_PATH%
pause

REM 网友的链接:https://blog.csdn.net/daoshuti/article/details/78212457
REM Keil官网的链接:http://www.keil.com/support/man/docs/uv4/uv4_commandline.htm
