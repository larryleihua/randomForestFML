.onAttach <- function(libname, pkgname) {
    RFver <- read.dcf(file=system.file("DESCRIPTION", package=pkgname),
                      fields="Version")
    packageStartupMessage(paste(pkgname, RFver))
    packageStartupMessage("A hacked randomForest R package 0.1.0 - add new features: sequential bootstrap")
}
