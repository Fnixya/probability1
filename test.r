set.seed(1)
x <- rexp(1000000) # simulated lifetime of 1000000 batteries 
hist(x, nclass = 250, probability=TRUE, border="white", col="blue")
t <- seq(0,15,by=.1)
points(t,dexp(t),type="l",col="blue",lwd=2)
