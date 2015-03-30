


running_time <- read.table("time",header=FALSE)

running_time <- running_time$V1



setEPS()
postscript("histogram.eps")
hist(running_time, freq = FALSE, breaks = 500, xlim = c(0, quantile(running_time, 0.99)), main="Histogram of running time")
lines(density(running_time), col="red") 
dev.off()

setEPS()
postscript("scatter plot.eps")
plot(running_time,xlab="iteration", ylab="running time", main="scatter plot of running time")
abline(h=mean(running_time), col="red", lty="dotted")
dev.off()

summary(running_time)
