## Test environments
* local OS X install, R 3.6.0
* ubuntu 14.04 (on travis-ci), R 3.6.0
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
* The claimed potentially spelled incorrectly words are not spelled incorrectly
  and I did not want to '' them all to avoid the check.
* I've commented out the calls to std::rand() and used' R's C random functions 
  instead (in the event y'all have other checks you do that winbuilder does
  not show).