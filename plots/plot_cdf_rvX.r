#library(ggplot2) 

# Random variable X ordenado por combinaciones 1-1, 2-1, 2-2, ....
# CDF

# Scenario (n vs 1)
cumsumrvX11 <- c(0, 1, 2, 3, 4, 5, 6, 6) / 6
cumsumrvX21 <- c(0, 1, 4, 9, 16, 25, 36, 36) / 36
cumsumrvX31 <- c(0, 1, 8, 27, 64, 125, 216, 216) / 216
cumsumrvX41 <- c(0, 1, 16, 81, 256, 625, 1296, 1296) / 1296
matplot(
    0:7, 
    cbind(cumsumrvX11, cumsumrvX21, cumsumrvX31, cumsumrvX41), 
    type='s',
    col = c("brown", "purple", "red", "black"),
    do.points = TRUE, pch = 16,col.points = "blue"
    )
legend("bottomright", legend = c("1 vs 1", "2 vs 1", "3 vs 1", "4 vs 1"), 
        col = c("brown", "purple", "red", "black"),
        lty = 1)
 

# Scenario (n vs 2)
cumsumrvX22 <- c(0, 1, 3, 4, 6, 8, 9, 11, 13, 15, 16, 18, 20, 22, 24, 25, 27, 29, 31, 33, 35, 36, 36) / 36
cumsumrvX32 <- c(0, 1, 4, 8, 11, 20, 27, 30, 39, 54, 64, 67, 76, 91, 112, 125, 128, 137, 152, 173, 200, 216, 216) / 216
cumsumrvX42 <- c(0, 1, 5, 16, 20, 48, 81, 85, 113, 189, 256, 260, 288, 364, 512, 625, 629, 657, 733, 881, 1125, 1296, 1296) / 1296
matplot(
    0:22, 
    cbind(cumsumrvX22, cumsumrvX32, cumsumrvX42), 
    type='s',
    col = c("brown", "purple", "blue"),
    do.points = TRUE, pch = 16,col.points = "blue"
    )
legend("bottomright", legend = c("2 vs 2", "3 vs 2", "4 vs 2"), 
        col = c("brown", "purple", "red"),
        lty = 1)





# Scenario (n vs 3)
cumsumrvX33 <- c(0, 1, 4, 7, 8, 11, 17, 20, 23, 26, 27, 30, 36, 39, 45, 51, 54, 57, 60, 63, 64, 67, 73, 76, 82, 88, 91, 97, 103, 109, 112, 115, 118, 121, 124, 125, 128, 134, 137, 143, 149, 152, 158, 164, 170, 173, 179, 185, 191, 197, 200, 203, 206, 209, 212, 215, 216, 216) / 216
cumsumrvX43 <- c(0, 1, 5, 9, 14, 18, 30, 46, 50, 66, 75, 79, 91, 107, 119, 155, 183, 187, 203, 231, 244, 248, 260, 276, 288, 324, 352, 364, 400, 460, 500, 504, 520, 548, 588, 605, 609, 621, 637, 649, 685, 713, 725, 761, 821, 861, 873, 909, 969, 1053, 1105, 1109, 1125, 1153, 1193, 1245, 1266, 1266) / 1266
matplot(
    0:57,
    cbind(cumsumrvX33, cumsumrvX43), 
    type='s',
    col = c("brown", "purple"),
    do.points = TRUE, pch = 16,col.points = "blue"
    )
legend("bottomright", legend = c("3 vs 3", "4 vs 3"), 
        col = c("brown", "purple"),
        lty = 1)



# Scenario (4 vs 4)
cumsumrvX44 <- c(1, 5, 11, 15, 16, 20, 32, 44, 48, 54, 66, 72, 76, 80, 81, 85, 97, 109, 113, 125, 149, 161, 173, 185, 189, 195, 207, 213, 225, 237, 243, 247, 251, 255, 256, 260, 272, 284, 288, 300, 324, 336, 348, 360, 364, 376, 400, 412, 436, 460, 472, 484, 496, 508, 512, 518, 530, 536, 548, 560, 566, 578, 590, 602, 608, 612, 616, 620, 624, 625, 629, 641, 653, 657, 669, 693, 705, 717, 729, 733, 745, 769, 781, 805, 829, 841, 853, 865, 877, 881, 893, 917, 929, 953, 977, 989, 1013, 1037, 1061, 1073, 1085, 1097, 1109, 1121, 1125, 1131, 1143, 1149, 1161, 1173, 1179, 1191, 1203, 1215, 1221, 1233, 1245, 1257, 1269, 1275, 1279, 1283, 1287, 1291, 1295, 1296)
plot(cumsumrvX44, type='s')

# Scenario (5 vs 7)
cumsumrvX75 <- c(1, 8, 29, 64, 99, 128, 135, 177, 282, 422, 576, 597, 702, 912, 1248, 1283, 1423, 1808, 1843, 2088, 2187, 2194, 2236, 2341, 2481, 2635, 2677, 2887, 3307, 3979, 4084, 4504, 5659, 5799, 6779, 7290, 7311, 7416, 7626, 7962, 8067, 8487, 9642, 9852, 11322, 12393, 12428, 12568, 12953, 13093, 14073, 15228, 15263, 15508, 16173, 16384, 16391, 16433, 16538, 16678, 16832, 16874, 17084, 17504, 18176, 18281, 18701, 19856, 19996, 20976, 21487, 21529, 21739, 22159, 22831, 23041, 23881, 26191, 26611, 29551, 31693, 31798, 32218, 33373, 33793, 36733, 40198, 40338, 41318, 43978, 45056, 45077, 45182, 45392, 45728, 45833, 46253, 47408, 47618, 49088, 50159, 50264, 50684, 51839, 52259, 55199, 58664, 58874, 60344, 64334, 66560, 66595, 66735, 67120, 67260, 68240, 69395, 69535, 70515, 73175, 75520, 75555, 75800, 76465, 77760, 78125, 78132, 78174, 78279, 78419, 78573, 78615, 78825, 79245, 79917, 80022, 80442, 81597, 81737, 82717, 83228, 83270, 83480, 83900, 84572, 84782, 85622, 87932, 88352, 91292, 93434, 93539, 93959, 95114, 95534, 98474, 101939, 102079, 103059, 105719, 106797, 106839, 107049, 107469, 108141, 108351, 109191, 111501, 111921, 114861, 117003, 117213, 118053, 120363, 121203, 127083, 134013, 134433, 137373, 145353, 149805, 149910, 150330, 151485, 151905, 154845, 158310, 158730, 161670, 169650, 176685, 176825, 177805, 180465, 185645, 187500, 187521, 187626, 187836, 188172, 188277, 188697, 189852, 190062, 191532, 192603, 192708, 193128, 194283, 194703, 197643, 201108, 201318, 202788, 206778, 209004, 209109, 209529, 210684, 211104, 214044, 217509, 217929, 220869, 228849, 235884, 236094, 237564, 241554, 249324, 253125, 253160, 253300, 253685, 253825, 254805, 255960, 256100, 257080, 259740, 262085, 262225, 263205, 265865, 271045, 275000, 275035, 275280, 275945, 277240, 279375, 279936)
plot(cumsumrvX75, type='s')
