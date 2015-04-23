

source("http://bioconductor.org/biocLite.R")
biocLite("impute")
require(impute)

load package "impute" from the packages menu
temp <- as.matrix(read.csv(file.choose(),header=T))

result <- impute.knn(temp)
write.table(result, file = "C://finalData1.csv",row.names=FALSE,col.names=FALSE, sep=",")