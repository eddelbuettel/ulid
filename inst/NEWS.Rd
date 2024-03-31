\name{NEWS}
\title{News for Package \pkg{ulid}}
\newcommand{\ghpr}{\href{https://github.com/eddelbuettel/ulid/pull/#1}{##1}}
\newcommand{\ghit}{\href{https://github.com/eddelbuettel/ulid/issues/#1}{##1}}

\section{Changes in version 0.4.0 (2024-04-xx)}{
  \itemize{
    \item New Maintainer
    \item Deleted several repository files no longer used or needed
    \item Added \code{.editorconfig}, \code{ChangeLog} and \code{cleanup}
    \item Converted NEWS.md to NEWS.Rd
    \item Simplified \code{R}/ directory to one source file
    \item Simplified \code{src/} removing redundant \code{Makevars}
    \item Added \code{ulid()} alias
    \item Updated / edited roxygen and README.md documention
    \item Removed vignette which was identical to README.md
    \item Switched continuous integration to GitHub Actions
  }
}

\section{Changes in version 0.3.0 (2019-07-27)}{
  \itemize{
    \item Updated libary
    \item Uses R C random bits vs \code{std::rand()}
    \item Vignette
    \item Converted to \pkg{tinytest}
  }
}

\section{Changes in version 0.2.0 (2019-07-04)}{
  \itemize{
    \item Polished version
  }
}

\section{Changes in version 0.1.0 (2018-12-28)}{
  \itemize{
    \item Initial release
  }
}
