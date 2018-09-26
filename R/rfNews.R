rfNews <- function() {
    newsfile <- file.path(system.file(package="randomForestFML"), "NEWS")
    file.show(newsfile)
}
