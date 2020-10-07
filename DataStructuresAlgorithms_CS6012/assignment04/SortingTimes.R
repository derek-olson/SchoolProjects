library(readr)
library(ggplot2)
library(lme4)
library(lattice)

setwd("~/DerekOlson/CS6012/assignment04")
data <- read_csv("sorting_times_quicksort2.csv", col_names = T)
#colnames(data) = c("Test","Size", "Time")

#insertionSort = data[1:6,2:3]
#sp = ggplot(insertionSort)+geom_line(aes(color='steelblue', x=insertionSort$`Threshold/size`, y=insertionSort$Time))
#sp+scale_x_continuous(trans='log2')

quicksort = data#[7:dim(data)[1],]
sp = ggplot(quicksort)+geom_line(aes(x=quicksort$Size, y=quicksort$Time, color = quicksort$Test))
sp+scale_x_continuous(trans='log2')

p <- ggplot(quicksort, aes(quicksort$Size, y=quicksort$Time,color = quicksort$Test)) +
  geom_point()
# Add regression line
p + geom_smooth(method = lm)

thresholdData <- read_csv("merge_threshold_compare.csv", col_names = T)
ggplot(thresholdData)+geom_line(aes(x=thresholdData$Size, y=thresholdData$Time, color = thresholdData$Test))
sp = ggplot(thresholdData)+geom_line(aes(x=thresholdData$Size, y=thresholdData$Time, color = thresholdData$Test))
sp+scale_x_continuous(trans='log2')

merge_quick = read_csv("merge_quick_compare.csv", col_names = T)
ggplot(merge_quick)+geom_line(aes(x=merge_quick$Size, y=merge_quick$Time, color = merge_quick$Test))

