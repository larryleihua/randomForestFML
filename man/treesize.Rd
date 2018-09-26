\name{treesize}
\alias{treesize}

\title{Size of trees in an ensemble}

\description{
Size of trees (number of nodes) in and ensemble.
}

\usage{
treesize(x, terminal=TRUE)
}

\arguments{
  \item{x}{an object of class \code{randomForestFML}, which contains a
    \code{forest} component.}
  \item{terminal}{count terminal nodes only (\code{TRUE}) or all nodes
    (\code{FALSE}}
}

\value{
A vector containing number of nodes for the trees in the
\code{randomForestFML} object.
}

\note{
  The \code{randomForestFML} object must contain the \code{forest}
  component; i.e., created with \code{randomForestFML(...,
    keep.forest=TRUE)}.
}

\seealso{\code{\link{randomForestFML}}}

\author{Andy Liaw \email{andy\_liaw@merck.com}}

\examples{
data(iris)
iris.rf <- randomForestFML(Species ~ ., iris)
hist(treesize(iris.rf))
}

\keyword{regression}
\keyword{classif}
