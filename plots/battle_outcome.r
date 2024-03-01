

win.graph()
par(mfrow=c(1, 6))

battle_out_distribution11 <- c(0.416667, 0.583333)
barplot(battle_out_distribution11 , ylim= c(0, 1), col="#ff3333", name= 0:1, main="1-1")

battle_out_distribution21 <- c(0.578704, 0.421296)
barplot(battle_out_distribution21 , ylim= c(0, 1), col="#ff3333", name= 0:1, main="2-1")

battle_out_distribution22 <- c(0.227623, 0.324074, 0.448302)
barplot(battle_out_distribution22 , ylim= c(0, 1), col="#ff3333", name= 0:2, main="2-2")


battle_out_distribution31 <- c(0.659722, 0.340278)
barplot(battle_out_distribution31 , ylim= c(0, 1), col="#ff3333", name= 0:1, main="3-1")

battle_out_distribution32 <- c(0.371656, 0.335777, 0.292567)
barplot(battle_out_distribution32 , ylim= c(0, 1), col="#ff3333", name= 0:2, main="3-2")

battle_out_distribution33 <- c(0.137603, 0.214699, 0.26466, 0.383038)
barplot(battle_out_distribution33 , ylim= c(0, 1), col="#ff3333", name= 0:3, main="3-3")

battle_out_distribution <- c(0.0448259, 0.0835701, 0.098904, 0.106645, 0.112557, 0.118201, 0.124921, 0.134438, 0.175938)
barplot(battle_out_distribution98 , ylim= c(0, 1), col="#ff3333", name= 0:8)
