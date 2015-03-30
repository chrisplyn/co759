
require(vcd)
require(MASS)

running_time <- read.table("time",header=FALSE)



# plot a graph
hist(running_time, freq = FALSE, breaks = 500, xlim = c(0, quantile(running_time, 0.99)))
plot(running_time)

summary(running_time)