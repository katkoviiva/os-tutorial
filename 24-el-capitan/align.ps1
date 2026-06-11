$path = "E:\os-tutorial\24-el-capitan\os-image.bin"
$file = Get-Item $path
$remainder = $file.Length % 512
if ($remainder -ne 0) {
    $padding = 512 - $remainder
    $bytes = New-Object byte[]($padding)
    [System.IO.File]::AppendAllBytes($path, $bytes)
    Write-Host "Padded file with $padding bytes."
} else {
    Write-Host "File is already aligned to 512 bytes."
}