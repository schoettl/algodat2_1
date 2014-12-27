distanceMatrix = readRDS("distance_matrix.rds")

head(distanceMatrix)
dims = dim(distanceMatrix)

cities = rownames(distanceMatrix)
cities = gsub(" ", "_", cities)

n = dims[1]
naCol = rep(NA, n)
graphDescription = data.frame(naCol, naCol, naCol)
k = 1 # row number
for (i in 1:n) {
  for (j in 1:i) {
    if (i == j) {
      next
    }
    graphDescription[k, ] = c(cities[i], round(distanceMatrix[i, j]), cities[j])
    k = k + 1
  }
}

head(graphDescription, 20)
write.table(graphDescription, file = "cities.txt", col.names = FALSE, row.names = FALSE, sep = " ", quote = FALSE)
