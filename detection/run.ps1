param (
    [string[]]$arguments
)

# Ensure that Java is installed and available in the PATH
$javaPath = "C:\Users\xgg\.jdks\openjdk-19\bin\java.exe"
if (-not (Test-Path $javaPath)) {
    Write-Host "Java is not installed or not found in the PATH."
    exit 1
}

$relativePath = Join-Path -Path $PSScriptRoot -ChildPath ".\jLZJD"
Set-Location -Path $relativePath

#$argumentsString = $args -join " "

$classPath = "C:\Users\xgg\PycharmProjects\mgr-polymorphic\detection\jLZJD\target\classes;C:\Users\xgg\.m2\repository\com\edwardraff\JSAT\0.0.8\JSAT-0.0.8.jar;C:\Users\xgg\.m2\repository\com\beust\jcommander\1.60\jcommander-1.60.jar;C:\Users\xgg\.m2\repository\com\google\guava\guava\21.0\guava-21.0.jar"

$argumentsString =@("-Dfile.encoding=UTF-8", "-Dsun.stdout.encoding=UTF-8", "-Dsun.stderr.encoding=UTF-8", "-classpath", "$classPath", "com.edwardraff.jlzjd.Main") + $arguments + @("-g", "-p", "2")

$output = & $javaPath $argumentsString 2>&1
Write-Output $output