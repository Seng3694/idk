@echo off

setlocal

rem option -nt for no tests
if /I "%1"=="-nt" (
	set exclude="ext out .vs test"
) else (
	set exclude="ext out .vs"
)

ruby %~dp0\loc.rb -f "c h inl" -e %exclude% -c %~dp0..
