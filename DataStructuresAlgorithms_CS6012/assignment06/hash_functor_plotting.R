library(readr)
library(ggplot2)
library(lme4)
library(lattice)

setwd("~/DerekOlson/CS6012/assignment06")
data <- read_csv("hash_functor_timing_collisions.csv", col_names = T)

ggplot(data)+geom_line(aes(x=data$Size, y=data$Time, color = data$Method))
sp = ggplot(data)+geom_line(aes(x=data$Size, y=data$Time, color = data$Method))
sp + ggtitle("Run time versus set size for 100,000 random strings") +
  xlab("Set Size") + ylab("Time (nanoseconds)")


p = ggplot(data)+geom_line(aes(x=data$Size, y=data$Collisions, color = data$Method))
p + ggtitle("Collisions versus set size for 100,000 random strings") +
  xlab("Set Size") + ylab("Collisions")