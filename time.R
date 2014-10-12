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
D$Algorithm <- factor(D$Algorithm)
for(i in 1:length(D$File)){
	D$Shape[i] <- do.call(rbind,strsplit(do.call(rbind, strsplit(as.character(D$File[i]), "-"))[,1],"/"))[,2]
}
D$Shape <- factor(D$Shape)

pdf("Time.pdf", width=11.7, height=8.3)
par(mar=c(5,3,2,2)+0.1)

trellis.par.set(superpose.symbol=list(pch = 1:length(unique(D$Algorithm))))
dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D,
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "All shapes",
                  auto.key = TRUE)
print(dataPlot, width=200)


dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, n <= 10^6)) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "All shapes",
                  auto.key = TRUE)
print(dataPlot, width=200)

# Circle
dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "circle")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Circle",
                  auto.key = TRUE)
print(dataPlot, width=200)


dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, n <= 10^6 & Shape == "circle")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Circle",
                  auto.key = TRUE)
                  
# Curve
dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "curve")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Curve",
                  auto.key = TRUE)
print(dataPlot, width=200)


dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, n <= 10^6 & Shape == "curve")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Curve",
                  auto.key = TRUE)
print(dataPlot, width=200)

# Lines
dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "lines")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Lines",
                  auto.key = TRUE)
print(dataPlot, width=200)


dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, n <= 10^6 & Shape == "lines")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Lines",
                  auto.key = TRUE)
print(dataPlot, width=200)

# Squares
dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "square")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Square",
                  auto.key = TRUE)
print(dataPlot, width=200)


dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, n <= 10^6 & Shape == "square")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Square",
                  auto.key = TRUE)
print(dataPlot, width=200)

# Triangle
dataPlot <- xyplot(Time ~ n,
                  groups = Algorithm,
                  data = D[which(with(D, Shape == "triangle")) ,],
                  type = c("a", "p"),
                  scales = list(x = list(log = 10),
                                y = list(log = FALSE)),
                  xlab = "Number of points", 
                  ylab = "Time (ms)",
                  main = "Triangle",
                  auto.key = TRUE)
print(dataPlot, width=200)
dev.off()
