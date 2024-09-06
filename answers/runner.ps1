<#

    *Just run the task to test your solution

    *    eg. of folder structure:
    
    |-|    OBI 2019/
    |-|    │── |fase 2/detetive.cpp
    |-|    │── answers/fase 2/
    |-|               │── temp.txt  (will be created if it doesn't exist)
    |-|               │── detetive/1/
    |-|                             │── 1.in
    |-|                             │── 1.out

#>
    
    
# args[0] must be the script to be tested
if ($args.Count -ne 1) {
    Write-Host ("1 argument required, " + $args.Count + " provided") -ForegroundColor Red
    Exit
}

# if code is not c or cpp exit
if ($args[0] -notmatch "\.c$|\.cpp$") {
    Write-Host "Error: code must be c or cpp" -ForegroundColor Red
    Exit
}

try{

    $code <#        #> = $args[0]
    $filename <#    #> = (Get-Item $code).BaseName
    $exe_file <#    #> = Join-Path (Get-Item $code).DirectoryName "$filename.exe"
    $folder_name <# #> = (Get-Item $code).DirectoryName.Split("\")[-1]
    
    $tests_folder <##> = Join-Path (Get-Item $code).DirectoryName "..\answers\$folder_name\$filename"
    $tests_folder <##> = Get-Item $tests_folder
    
    $output_file <# #> = Join-Path $tests_folder "output.txt"
}
catch{
    Write-Host "The file extructed is wrong" -ForegroundColor Red
    Exit
}
    


# Create the output_file code if it doesn't exist
if (!(Test-Path $output_file)) {
    New-Item $output_file -ItemType File | out-null
}


# TODO: block if isnt a cpp file or if the folder structure is wrong
# Check if cases folder exists, if not exit
if (!(Test-Path $tests_folder)) {
    Write-Host "Error: Test folder not found!" -ForegroundColor Red
    Exit
}

# Compiling the code
Write-Host "Compiling..." -ForegroundColor Yellow
try {
    g++ -g "$code" -o "$exe_file" -Wall
} catch {
    Write-Host "Error in compiling file!" -ForegroundColor Red
    Exit
}


Write-Host "`n`nCompiled successfully. Running cases...`n`n" -ForegroundColor Magenta
# `n instead of \n, powershell is cursed


# Run all test case folders
Get-ChildItem $tests_folder -Directory | ForEach-Object {
    Write-Host ("Test block: " + $_.Name) -ForegroundColor Yellow
    
    
    # * each folder have a pair of number.in and number.sol
    # TODO : skip if number.sol doesn't exist
    Get-ChildItem $_.FullName -Filter *.in | ForEach-Object {
        $input_file <# #> = $_.FullName
        $answer_file <##> = $_.FullName.Replace(".in", ".sol")
        
        
        Get-Content $input_file | & $exe_file | Tee-Object $output_file | Out-Null
        
        
        # if is not equal break
        # TODO : implement trimming output when possible
        if ((Get-Content $output_file) -ne (Get-Content $answer_file)) {
            Write-Host ("$filename.cpp returned an error in case " + $_.BaseName) -ForegroundColor Red

            # ! break is not working, is exiting instead of jump to the next block case
            $break = $true
            $break = $break # trick to avoid unused warning
            break
        }
    }

    if (-Not $break) {
        Write-Host "Test block completed!" -ForegroundColor Green
    }
}

Write-Host "The question '$filename.cpp' is correct" -ForegroundColor Green