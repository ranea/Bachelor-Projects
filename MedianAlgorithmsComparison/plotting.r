#!/usr/bin/env Rscript

args = commandArgs(trailingOnly=TRUE)
# test if there is at least one argument: if not, return an error
if (length(args)==0) {
  stop("At least one argument must be supplied (input file).\n", call.=FALSE)
}

data <- read.csv(args[1],head=TRUE,sep=",")
mycolors = c('red','blue','green')
with(data,plot(size,time,col=mycolors[algorithm]))
with(data,legend('topleft',legend=levels(algorithm),col=mycolors,pch=1,title='Algorithm'))
title('Execution time of median fiding algorithms')
