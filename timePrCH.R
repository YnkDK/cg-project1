tryCatch(
	library(lattice),
	error= function(c) install.packages('lattice', repos='http://mirrors.dotsrc.org/cran/')
)
tryCatch(
	library(stringr),
	error= function(c) install.packages('stringr', repos='http://mirrors.dotsrc.org/cran/')
)

args <- commandArgs(trailingOnly = TRUE)

D <- read.table(args[1], fill = TRUE)
# Remove the garbage column
D$V1 <- NULL
# Name the remaining columns
colnames(D) <- c("ch", "n", "Time", "Algorithm", "File")

D$Time <- D$Time / 1000000
# Factorize

for(i in 1:length(D$File)){
	D$Shape[i] <- do.call(rbind,strsplit(do.call(rbind, strsplit(as.character(D$File[i]), "-"))[,1],"/"))[,2]
}
D$Shape <- factor(D$Shape)
D <- D[D$Algorithm != "IO", ]
D$Algorithm <- factor(D$Algorithm)
summary(D)
###########################
## Times per convex hull ##
###########################
pdf("timePrCH.pdf", width=11.7, height=8.3)
par(mar=c(5,3,2,2)+0.1)


trellis.par.set(superpose.symbol=list(pch = 1:length(D$Algorithm)))
# Triangle
dataPlot <- xyplot(Time/ch ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "triangle" & Algorithm != "IO")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms) per convex hull point",
                  main = "Triangles",
                  auto.key = TRUE)
print(dataPlot, width=200)

# Circle
dataPlot <- xyplot(Time/ch ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "circle" & Algorithm != "IO")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms) per convex hull point",
                  main = "Circle",
                  auto.key = TRUE)
print(dataPlot, width=200)

# Curve
dataPlot <- xyplot(Time/ch ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "curve" & Algorithm != "IO")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms) per convex hull point",
                  main = "Curve",
                  auto.key = TRUE)
print(dataPlot, width=200)                  
# Square
dataPlot <- xyplot(Time/ch ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "square" & Algorithm != "IO")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms) per convex hull point",
                  main = "Square",
                  auto.key = TRUE)
print(dataPlot, width=200)                
# Lines
dataPlot <- xyplot(Time/ch ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "lines" & Algorithm != "IO")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms) per convex hull point",
                  main = "Lines",
                  auto.key = TRUE)                  
print(dataPlot, width=200)
dev.off()
