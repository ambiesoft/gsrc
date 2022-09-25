
$target = 'debug'
# Write-Host($args.Count)
if ( $args.Count -gt 0 ) {
  $target = $args[0]
  # Write-Host("aaa")
}
Write-Host("CURRET_DEBUGDIR is set to $($target)")
$Env:CURRENT_DEBUGDIR = $target
