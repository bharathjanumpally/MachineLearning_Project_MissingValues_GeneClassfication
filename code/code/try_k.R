rm(list=ls())
with_my_missing <- as.matrix(read.csv(file="C:/Users/ramsundar/Desktop/try/1/caioriginal12.csv",head=TRUE,sep=","))
t_with_my_missing <- t(with_my_missing)
for(npcs in 48:48)
{
result <- completeObs(pca(t_with_my_missing, nPcs=npcs, method="bpca"))
result<-t(result)
filename<-paste("C:/Users/ramsundar/Desktop/try/1/pca_bpca_",toString(npcs),".csv",sep="")
print(paste("Created :", filename, sep=""))
write.csv(result, file =filename,row.names=FALSE)
}