/* Definition of a triangle mesh for a cow */

#pragma warning(disable: 4305)
#pragma once

struct cow_ {
	int nov;
	int nof;
	float verts[1542];
	int faces[3072];
};

struct cow_ cow = {

	514, /* number of vertices */

	1024, /* number of faces */

	{ /* vertices */
	0.148581, -0.043734, -0.093620,
	0.173813, -0.030980, -0.075680,
	0.178130, -0.083062, -0.060402,
	0.123696, -0.114001, -0.062753,
	0.151700, -0.117413, -0.039762,
	0.213397, -0.082558, -0.032744,
	0.220611, -0.045605, -0.027864,
	0.185900, -0.113663, -0.041757,
	0.210242, -0.090531, 0.035178,
	0.075892, -0.111639, 0.001925,
	0.222741, -0.002954, -0.041052,
	0.202856, 0.016622, -0.059246,
	0.183656, 0.001185, -0.096280,
	-0.181581, -0.134172, -0.069491,
	-0.205040, -0.122240, -0.072303,
	-0.149106, -0.117407, -0.092314,
	-0.137895, -0.134810, -0.081433,
	-0.086900, -0.122943, -0.080186,
	-0.085823, -0.135399, -0.046428,
	-0.129663, -0.141791, -0.034417,
	-0.230223, -0.125505, -0.033049,
	0.005382, -0.100850, -0.060311,
	0.017222, -0.105697, -0.039290,
	0.011234, -0.112112, 0.001987,
	-0.177594, -0.137614, 0.040256,
	0.088871, -0.213360, -0.080992,
	0.102408, -0.227751, -0.091013,
	0.118665, -0.222382, -0.084503,
	0.096169, -0.269773, -0.091744,
	0.133465, -0.268420, -0.103273,
	0.115321, -0.264539, -0.069689,
	0.101276, -0.263309, -0.067922,
	-0.356632, -0.133451, -0.075657,
	-0.339864, -0.110031, -0.090092,
	-0.390997, -0.138665, -0.111363,
	-0.376147, -0.091758, -0.112708,
	-0.426220, -0.141099, -0.074109,
	-0.392481, -0.195674, -0.105131,
	-0.427072, -0.139827, -0.090342,
	-0.414461, -0.214126, -0.090250,
	-0.379734, -0.229949, -0.099936,
	-0.377292, -0.178408, -0.092708,
	-0.394798, -0.189406, -0.081816,
	-0.416517, -0.109276, -0.064273,
	-0.390892, -0.125863, -0.061774,
	-0.408733, -0.093373, -0.088250,
	0.127614, -0.164131, -0.084135,
	0.128354, -0.116537, -0.089371,
	0.074748, -0.159469, -0.091039,
	0.067376, -0.115747, -0.073598,
	0.085409, -0.116187, -0.065142,
	0.112515, -0.127482, -0.103429,
	0.111674, -0.074679, -0.119570,
	0.115567, -0.180789, -0.070283,
	0.096976, -0.176383, -0.063933,
	0.139270, -0.054892, -0.110319,
	0.071156, -0.098818, -0.106872,
	0.070729, -0.060457, -0.116332,
	0.051060, -0.066737, -0.092198,
	0.237651, 0.245970, -0.001862,
	0.210074, 0.228894, -0.016227,
	0.249276, 0.228491, -0.029810,
	0.264844, 0.161624, -0.049107,
	0.209119, 0.143982, -0.050329,
	0.251945, 0.074995, -0.049631,
	0.284359, 0.046714, -0.018011,
	0.292408, 0.101289, -0.040143,
	0.322010, 0.285447, -0.033281,
	0.338731, 0.110334, -0.022703,
	0.334065, 0.138838, -0.047041,
	0.332364, 0.175972, -0.056356,
	0.313607, 0.237879, -0.046275,
	0.133907, 0.221891, 0.006407,
	0.187004, 0.207542, -0.032583,
	0.178508, 0.155145, -0.058372,
	0.203375, 0.056320, -0.072159,
	0.172522, 0.038339, -0.116756,
	0.192880, 0.062230, -0.098461,
	0.180314, 0.117785, -0.081840,
	0.133395, 0.214199, -0.029521,
	0.152539, 0.175278, -0.062142,
	0.166328, -0.002842, -0.109091,
	0.171494, 0.080238, -0.110508,
	0.123741, -0.022364, -0.119149,
	0.133157, 0.011582, -0.126906,
	0.072233, 0.222486, -0.014558,
	0.131199, 0.072427, -0.124746,
	0.117939, 0.141811, -0.095583,
	0.110480, 0.191259, -0.059657,
	-0.133623, 0.210450, -0.022422,
	-0.015584, 0.216706, -0.000014,
	-0.003315, 0.194780, -0.043186,
	-0.055219, 0.192191, -0.045057,
	-0.006054, 0.149467, -0.082513,
	-0.071085, 0.105297, -0.122174,
	0.014519, 0.119432, -0.099933,
	0.001576, 0.075986, -0.121920,
	-0.025460, 0.013737, -0.138660,
	0.014652, 0.019804, -0.126495,
	-0.071194, -0.025635, -0.154242,
	-0.071909, -0.065027, -0.138278,
	0.018102, -0.060037, -0.095016,
	0.013888, -0.081492, -0.078081,
	-0.176458, 0.221046, 0.000104,
	-0.178260, 0.194622, -0.073680,
	-0.127381, 0.172492, -0.075174,
	-0.194890, 0.161192, -0.090537,
	-0.205202, 0.132201, -0.120943,
	-0.147116, 0.077730, -0.152354,
	-0.121101, 0.037835, -0.165985,
	-0.128892, -0.034859, -0.168910,
	-0.126334, -0.075486, -0.150403,
	-0.130781, -0.099738, -0.127433,
	-0.086626, -0.093325, -0.121714,
	-0.225048, 0.207500, -0.072511,
	-0.240647, 0.195775, -0.103892,
	-0.248280, 0.179643, -0.113235,
	-0.229361, 0.146825, -0.117817,
	-0.212444, 0.082810, -0.144866,
	-0.186296, 0.012424, -0.168184,
	-0.217820, -0.030953, -0.154564,
	-0.186948, -0.049422, -0.161580,
	-0.217568, -0.071906, -0.128118,
	-0.176956, -0.091202, -0.133809,
	0.091505, 0.002305, -0.129044,
	0.070081, 0.187334, -0.065811,
	0.080059, 0.132408, -0.102386,
	0.134387, 0.029810, -0.128771,
	0.040916, -0.100517, -0.057744,
	0.059709, -0.012596, -0.110625,
	-0.267241, 0.010770, -0.136371,
	-0.258711, -0.055545, -0.097901,
	-0.313978, 0.231720, -0.002061,
	-0.277567, 0.218878, -0.041757,
	-0.279430, 0.205259, -0.081221,
	-0.282619, 0.180697, -0.107580,
	-0.272445, 0.089474, -0.120780,
	-0.261039, 0.047362, -0.137408,
	-0.283083, -0.048356, -0.098563,
	-0.228101, -0.085232, -0.088465,
	-0.334767, 0.131304, -0.123626,
	-0.320026, 0.082498, -0.129727,
	-0.303338, 0.009063, -0.140802,
	-0.311653, -0.038773, -0.122416,
	-0.321662, -0.082004, -0.098665,
	-0.382414, 0.225594, -0.050718,
	-0.384144, 0.205171, -0.083585,
	-0.366658, 0.159285, -0.114153,
	-0.316213, 0.043300, -0.139389,
	-0.414163, 0.231618, -0.017324,
	-0.357425, 0.077762, -0.122541,
	-0.343384, -0.086779, -0.116919,
	-0.415537, 0.219968, -0.052322,
	-0.418236, 0.219906, 0.001647,
	-0.447166, 0.184890, -0.048092,
	-0.403671, 0.179538, -0.088215,
	-0.387721, 0.058151, -0.115098,
	-0.370211, -0.012841, -0.128246,
	-0.449008, 0.203426, -0.026547,
	-0.425618, 0.074965, -0.087603,
	-0.398621, -0.038395, -0.101414,
	-0.448088, 0.181150, -0.019826,
	-0.444355, 0.137871, -0.037082,
	-0.423359, 0.021913, -0.064107,
	-0.402002, -0.045819, -0.082438,
	-0.406952, -0.248632, -0.111775,
	-0.359214, -0.271889, -0.101886,
	-0.401933, -0.277334, -0.104717,
	-0.387906, -0.268605, -0.082602,
	-0.409516, -0.273874, -0.091145,
	-0.373789, -0.278556, -0.083000,
	-0.430240, 0.069261, -0.037689,
	-0.438123, 0.171917, 0.000382,
	-0.437821, 0.131343, -0.021571,
	-0.468494, 0.146453, 0.003431,
	-0.459391, 0.039005, 0.004481,
	-0.449499, 0.224355, 0.003968,
	-0.412933, 0.247719, -0.003446,
	-0.464948, 0.188387, -0.008263,
	-0.453165, 0.201238, -0.012901,
	-0.443588, 0.042376, -0.006292,
	0.400926, 0.249590, -0.063246,
	0.422957, 0.258337, -0.048679,
	0.443459, 0.227223, -0.018390,
	0.385244, 0.279343, -0.025702,
	0.437005, 0.240182, -0.006622,
	0.447003, 0.183645, -0.036821,
	0.389671, 0.160995, -0.061781,
	0.370697, 0.276240, -0.043498,
	0.453166, 0.152984, -0.036350,
	0.353740, 0.202599, -0.065931,
	0.493936, 0.178003, -0.028492,
	0.510906, 0.182858, -0.014861,
	0.516695, 0.158780, -0.020203,
	0.503661, 0.132456, -0.013219,
	0.487760, 0.148981, -0.038620,
	0.465151, 0.139199, -0.031558,
	0.408911, 0.125695, -0.034993,
	0.452532, 0.129889, -0.018789,
	0.361301, 0.151475, -0.060119,
	0.352999, 0.240839, -0.056763,
	0.330758, 0.230909, -0.052910,
	0.358230, 0.300902, -0.029619,
	0.332996, 0.302410, -0.024773,
	0.328435, 0.266731, -0.082792,
	0.300857, 0.262397, -0.036444,
	0.322475, 0.250076, -0.079264,
	0.349987, 0.285615, -0.096382,
	0.329211, 0.280915, -0.140894,
	0.342951, 0.285233, -0.123624,
	0.323459, 0.247008, -0.106561,
	0.336434, 0.225491, -0.102669,
	0.357948, 0.255643, -0.078217,
	0.337027, 0.251640, -0.080689,
	0.331963, 0.262467, -0.144074,
	0.321218, 0.294215, -0.000025,
	0.148885, -0.042873, 0.095928,
	0.170894, -0.070435, 0.071656,
	0.129237, -0.112916, 0.054498,
	0.177465, -0.100971, 0.051286,
	0.219738, -0.044209, 0.029387,
	0.185109, -0.113965, 0.037299,
	0.187369, -0.022065, 0.065550,
	0.223918, 0.019473, 0.044862,
	0.184911, 0.000548, 0.092972,
	-0.205679, -0.122988, 0.070749,
	-0.176766, -0.134100, 0.075095,
	-0.181205, -0.109590, 0.088002,
	-0.135709, -0.133773, 0.082020,
	-0.131127, -0.117733, 0.092056,
	-0.075651, -0.118847, 0.079869,
	-0.090640, -0.137891, 0.036637,
	-0.130661, -0.140817, 0.038701,
	-0.232543, -0.125689, 0.032806,
	0.001302, -0.101396, 0.060926,
	0.014273, -0.107245, 0.038515,
	0.097982, -0.268999, 0.096743,
	0.113473, -0.224873, 0.090253,
	0.130756, -0.255256, 0.081924,
	0.099334, -0.268520, 0.069208,
	0.120887, -0.266839, 0.069040,
	0.102915, -0.205697, 0.066854,
	-0.373317, -0.148141, 0.102635,
	-0.363254, -0.139100, 0.068409,
	-0.325293, -0.088038, 0.098326,
	-0.373078, -0.120138, 0.112069,
	-0.399073, -0.148857, 0.108693,
	-0.428185, -0.135727, 0.078275,
	-0.405846, -0.083855, 0.089061,
	-0.415593, -0.103102, 0.067099,
	-0.426294, -0.139970, 0.091234,
	-0.414329, -0.211674, 0.089487,
	-0.370787, -0.157334, 0.083928,
	-0.389902, -0.205794, 0.085251,
	-0.412206, -0.113821, 0.063127,
	0.121406, -0.196383, 0.083979,
	0.091497, -0.228955, 0.086928,
	0.070983, -0.153073, 0.084863,
	0.071877, -0.115992, 0.067985,
	0.127336, -0.115149, 0.095822,
	0.114533, -0.142991, 0.101872,
	0.106193, -0.075166, 0.119861,
	0.114310, -0.167481, 0.068106,
	0.119820, -0.115303, 0.061726,
	0.137695, -0.059103, 0.111639,
	0.069983, -0.068295, 0.115214,
	0.074376, -0.124020, 0.100804,
	0.051668, -0.081588, 0.080438,
	0.056545, -0.021861, 0.108865,
	0.253347, 0.249697, 0.012563,
	0.200114, 0.210261, 0.031240,
	0.245430, 0.225559, 0.029846,
	0.265098, 0.185857, 0.043539,
	0.256702, 0.140109, 0.048299,
	0.233431, 0.089738, 0.054933,
	0.277040, 0.090438, 0.041200,
	0.297404, 0.065823, 0.016814,
	0.333231, 0.115720, 0.033703,
	0.336825, 0.138346, 0.047090,
	0.331826, 0.180506, 0.056938,
	0.328928, 0.229981, 0.051155,
	0.165361, 0.217997, 0.024335,
	0.192690, 0.170215, 0.047972,
	0.202680, 0.057657, 0.072977,
	0.152852, 0.182754, 0.056755,
	0.169146, 0.006604, 0.111378,
	0.193384, 0.062102, 0.097463,
	0.174333, 0.105026, 0.096639,
	0.175234, 0.051860, 0.116048,
	0.123741, -0.022364, 0.119149,
	0.134308, 0.018568, 0.128047,
	0.133340, 0.063036, 0.128130,
	0.123196, 0.099508, 0.113084,
	0.103447, 0.141495, 0.098493,
	0.088437, 0.185127, 0.069480,
	0.070434, 0.217982, 0.022382,
	-0.003932, 0.197748, 0.039607,
	-0.023718, 0.181240, 0.054382,
	-0.013375, 0.149806, 0.081474,
	-0.053265, 0.157274, 0.081999,
	-0.045979, 0.122397, 0.108626,
	0.016314, 0.081864, 0.118587,
	-0.023687, 0.079264, 0.125449,
	0.022087, 0.046428, 0.126634,
	-0.072723, 0.057682, 0.146855,
	0.006342, 0.015367, 0.125370,
	0.017373, -0.008995, 0.113887,
	-0.056701, -0.031884, 0.146545,
	0.016371, -0.050559, 0.100123,
	-0.085630, -0.084189, 0.132610,
	0.014248, -0.081133, 0.079039,
	-0.072471, 0.210697, 0.018597,
	-0.097854, 0.192755, 0.053891,
	-0.152872, 0.191153, 0.069882,
	-0.171515, 0.166284, 0.083082,
	-0.118228, 0.144375, 0.097109,
	-0.207980, 0.157095, 0.101963,
	-0.089132, 0.089708, 0.134620,
	-0.142544, 0.073446, 0.154042,
	-0.131289, 0.029420, 0.168223,
	-0.070574, 0.005992, 0.155896,
	-0.130965, -0.014362, 0.170141,
	-0.128130, -0.059168, 0.161331,
	-0.131886, -0.099012, 0.128458,
	-0.214972, 0.207081, 0.068831,
	-0.241650, 0.196850, 0.104382,
	-0.221773, 0.138036, 0.121442,
	-0.192197, 0.073948, 0.151032,
	-0.228235, 0.049088, 0.150154,
	-0.182956, 0.009611, 0.169025,
	-0.193279, -0.041583, 0.162536,
	-0.218041, -0.064232, 0.135953,
	-0.180050, -0.086574, 0.139432,
	-0.226083, -0.084066, 0.091776,
	0.092629, 0.002461, 0.129288,
	0.084439, 0.060911, 0.122463,
	0.042927, -0.108608, 0.049059,
	-0.271480, 0.093813, 0.119479,
	-0.260273, 0.046296, 0.137789,
	-0.264658, 0.019924, 0.137876,
	-0.261069, -0.018894, 0.125320,
	-0.257425, -0.056842, 0.096266,
	-0.281355, 0.221474, 0.030230,
	-0.276521, 0.204285, 0.083112,
	-0.286775, 0.177562, 0.109893,
	-0.289710, 0.010108, 0.140566,
	-0.287828, -0.049696, 0.097395,
	-0.314440, 0.148353, 0.116895,
	-0.323498, 0.091034, 0.129240,
	-0.306500, -0.033539, 0.122602,
	-0.369249, 0.232498, 0.023412,
	-0.380989, 0.224004, 0.054182,
	-0.349361, 0.201546, 0.087597,
	-0.342280, 0.160508, 0.115460,
	-0.316232, 0.020225, 0.140721,
	-0.328182, -0.060084, 0.121926,
	-0.385974, 0.200527, 0.087596,
	-0.363424, 0.140587, 0.117627,
	-0.388480, 0.066786, 0.113982,
	-0.369015, -0.019396, 0.129319,
	-0.449571, 0.201262, 0.028879,
	-0.416038, 0.219473, 0.051948,
	-0.445509, 0.175871, 0.052542,
	-0.410801, 0.180124, 0.082611,
	-0.380455, -0.095665, 0.109284,
	-0.424929, 0.073781, 0.087581,
	-0.400950, -0.023604, 0.101348,
	-0.447942, 0.171892, 0.029646,
	-0.443520, 0.129108, 0.041525,
	-0.423185, 0.020238, 0.063439,
	-0.411031, -0.267809, 0.107733,
	-0.401459, -0.226897, 0.104048,
	-0.400390, -0.278362, 0.103637,
	-0.358244, -0.275400, 0.097841,
	-0.405384, -0.274158, 0.083461,
	-0.379735, -0.226171, 0.099638,
	-0.380353, -0.271971, 0.083215,
	-0.401286, -0.047376, 0.082964,
	-0.435016, 0.126346, 0.027628,
	-0.429921, 0.067463, 0.037275,
	-0.459272, 0.193344, 0.011919,
	-0.418007, 0.235269, 0.014983,
	-0.444993, -0.004710, 0.006599,
	-0.445632, 0.183409, 0.003826,
	-0.456866, 0.037083, -0.008003,
	0.404364, 0.243902, 0.063689,
	0.422987, 0.258689, 0.048865,
	0.422432, 0.222794, 0.050658,
	0.371151, 0.278870, 0.041527,
	0.439992, 0.233273, 0.016560,
	0.386693, 0.281847, 0.017826,
	0.393207, 0.178067, 0.059678,
	0.353016, 0.241489, 0.056215,
	0.456083, 0.171457, 0.034204,
	0.483196, 0.195624, 0.015696,
	0.355338, 0.203067, 0.065442,
	0.497087, 0.177062, 0.030955,
	0.521587, 0.176789, 0.010523,
	0.517414, 0.160817, 0.015122,
	0.476735, 0.146497, 0.037584,
	0.463714, 0.129679, 0.016693,
	0.407681, 0.140811, 0.047292,
	0.515053, 0.147059, 0.023394,
	0.398230, 0.121588, 0.033555,
	0.371885, 0.153226, 0.063821,
	0.336726, 0.109242, 0.018690,
	0.353085, 0.303713, 0.030246,
	0.324227, 0.291213, 0.027617,
	0.342020, 0.274936, 0.058919,
	0.331717, 0.270234, 0.081526,
	0.301686, 0.258943, 0.038833,
	0.321432, 0.250030, 0.078710,
	0.324435, 0.248936, 0.110530,
	0.330150, 0.277632, 0.146213,
	0.335663, 0.229696, 0.104782,
	0.355241, 0.281705, 0.094292,
	0.356018, 0.250472, 0.074078,
	0.337632, 0.254141, 0.084974,
	-0.243142, -0.109667, -0.075901,
	-0.257595, -0.131448, 0.000000,
	-0.263970, -0.138326, -0.039320,
	-0.321950, -0.145989, -0.052677,
	-0.288592, -0.141849, -0.053432,
	-0.343903, -0.146253, -0.042435,
	-0.349661, -0.140583, 0.000107,
	-0.306413, -0.143244, -0.001323,
	-0.288344, -0.146494, -0.033741,
	-0.429015, -0.094478, -0.055585,
	-0.446567, -0.056589, -0.045278,
	-0.435031, 0.045893, -0.028384,
	-0.434620, -0.049643, -0.068119,
	-0.331111, -0.173400, -0.051787,
	-0.349506, -0.152045, -0.054187,
	-0.275442, -0.170171, -0.042364,
	-0.285795, -0.170092, -0.052578,
	-0.253620, -0.103559, 0.085291,
	-0.311944, -0.110077, 0.089581,
	-0.238512, -0.111441, 0.072843,
	-0.322334, -0.143564, 0.055130,
	-0.276969, -0.141416, 0.051370,
	-0.287033, -0.147293, 0.032917,
	-0.349940, -0.143930, 0.053905,
	-0.333384, -0.147516, 0.041409,
	-0.439016, -0.077660, 0.050792,
	-0.446381, -0.043668, 0.044217,
	-0.434692, -0.050870, 0.067696,
	-0.286196, -0.170358, 0.051944,
	-0.278556, -0.172313, 0.041775,
	-0.342241, -0.174607, 0.051720,
	0.145496, -0.310558, -0.125869,
	0.164090, -0.306836, -0.112624,
	0.116932, -0.308642, -0.117752,
	0.109858, -0.259992, -0.099503,
	0.160981, -0.301279, -0.084007,
	0.111408, -0.307601, -0.088048,
	0.129958, -0.314453, -0.068357,
	0.131305, -0.287577, -0.067213,
	-0.364757, -0.280356, -0.122856,
	-0.353148, -0.315769, -0.140084,
	-0.332630, -0.312008, -0.126665,
	-0.384775, -0.313764, -0.131836,
	-0.391880, -0.266263, -0.113595,
	-0.390790, -0.312673, -0.102234,
	-0.370412, -0.319664, -0.082500,
	-0.336578, -0.309148, -0.094516,
	0.136096, -0.274445, 0.105836,
	0.165099, -0.304438, 0.112117,
	0.146666, -0.309961, 0.125989,
	0.110892, -0.261474, 0.100020,
	0.116666, -0.309546, 0.117131,
	0.109415, -0.305717, 0.088480,
	0.118807, -0.305716, 0.068686,
	0.138668, -0.315432, 0.091313,
	0.160176, -0.308185, 0.077075,
	-0.365410, -0.274782, 0.115273,
	-0.331547, -0.309635, 0.126316,
	-0.351842, -0.315167, 0.140205,
	-0.391301, -0.266672, 0.114237,
	-0.385048, -0.314667, 0.131228,
	-0.392983, -0.310768, 0.102681,
	-0.382571, -0.310854, 0.082889,
	-0.360635, -0.320640, 0.105513,
	-0.336831, -0.313341, 0.091358,
	0.412791, 0.225247, -0.058266,
	0.364196, 0.309376, -0.067933,
	0.417979, 0.316132, -0.081646,
	0.379255, 0.295431, -0.081178,
	0.394314, 0.318706, -0.098176,
	0.358566, 0.293577, -0.089863,
	0.404066, 0.302256, -0.092348,
	0.345286, 0.274259, -0.059924,
	0.343362, 0.309228, -0.081473,
	0.351904, 0.314903, 0.080401,
	0.380107, 0.315701, 0.081970,
	0.369150, 0.290980, 0.074785,
	0.423497, 0.313416, 0.079452,
	0.357607, 0.292614, 0.088786,
	0.398234, 0.300838, 0.094675,
	0.396158, 0.316871, 0.098929,
	-0.444261, -0.085623, 0.008084,
	-0.432843, -0.092538, -0.008713,
	-0.464789, -0.133149, -0.004635,
	-0.473799, -0.104103, 0.016567,
	-0.500648, -0.146198, 0.016853,
	-0.476543, -0.036715, 0.009767,
	-0.514881, -0.124268, 0.009093,
	-0.521841, -0.154381, 0.015064,
	-0.496821, -0.063382, 0.002957,
	-0.497739, -0.085373, -0.020266,
	-0.497560, -0.126891, -0.020959,
	-0.455574, -0.030089, -0.017531,
	-0.460208, -0.072962, -0.028765,
	-0.475650, -0.118185, -0.027628,
	-0.490836, -0.150540, -0.001006
	},

	{ /* face indices */
	0, 1, 2,
	2, 3, 0,
	3, 2, 4,
	2, 1, 5,
	2, 5, 7,
	4, 9, 3,
	11, 1, 12,
	1, 10, 6,
	6, 5, 1,
	1, 11, 10,
	13, 15, 16,
	17, 18, 19,
	19, 13, 16,
	20, 14, 13,
	18, 21, 22,
	23, 231, 18,
	19, 24, 13,
	31, 30, 25,
	32, 41, 151,
	38, 36, 43,
	37, 38, 34,
	40, 37, 41,
	37, 34, 41,
	36, 39, 42,
	26, 452, 25,
	56, 48, 49,
	51, 47, 46,
	46, 27, 26,
	48, 52, 51,
	30, 27, 53,
	3, 50, 54,
	47, 3, 53,
	55, 0, 47,
	52, 55, 47,
	58, 57, 56,
	48, 56, 52,
	64, 63, 62,
	65, 64, 66,
	69, 66, 62,
	70, 62, 71,
	205, 61, 59,
	6, 65, 276,
	72, 59, 60,
	74, 73, 63,
	74, 63, 64,
	11, 64, 65,
	73, 61, 62,
	405, 276, 65,
	71, 62, 61,
	78, 74, 75,
	75, 76, 77,
	79, 60, 73,
	80, 73, 74,
	0, 81, 1,
	82, 78, 77,
	81, 76, 12,
	81, 12, 1,
	81, 0, 83,
	81, 83, 84,
	81, 84, 127,
	76, 127, 86,
	82, 86, 87,
	80, 87, 88,
	80, 88, 85,
	92, 89, 91,
	94, 93, 95,
	99, 97, 98,
	100, 99, 98,
	89, 103, 90,
	105, 104, 92,
	107, 106, 105,
	108, 107, 94,
	111, 110, 99,
	112, 111, 100,
	15, 112, 113,
	115, 114, 104,
	116, 115, 104,
	117, 116, 106,
	118, 117, 107,
	122, 120, 121,
	57, 124, 83,
	125, 88, 87,
	124, 84, 83,
	55, 52, 83,
	52, 57, 83,
	50, 3, 9,
	128, 58, 49,
	128, 49, 50,
	9, 22, 50,
	129, 124, 57,
	9, 23, 22,
	128, 21, 102,
	58, 102, 101,
	58, 101, 98,
	84, 98, 96,
	86, 96, 95,
	126, 95, 93,
	126, 93, 91,
	125, 91, 90,
	105, 92, 93,
	109, 94, 96,
	99, 109, 97,
	17, 113, 102,
	21, 18, 17,
	106, 104, 105,
	118, 107, 108,
	119, 118, 109,
	121, 119, 110,
	123, 121, 111,
	15, 123, 112,
	129, 57, 58,
	136, 116, 117,
	137, 136, 118,
	130, 137, 119,
	131, 130, 120,
	89, 132, 103,
	134, 133, 114,
	135, 134, 114,
	136, 115, 116,
	122, 123, 15,
	133, 132, 89,
	141, 140, 136,
	143, 142, 130,
	144, 143, 138,
	146, 145, 134,
	147, 146, 135,
	149, 177, 132,
	145, 149, 132,
	150, 147, 141,
	155, 154, 152,
	45, 160, 35,
	154, 158, 152,
	159, 154, 155,
	160, 159, 156,
	162, 161, 154,
	163, 162, 159,
	164, 163, 160,
	151, 35, 157,
	148, 157, 156,
	150, 156, 155,
	146, 155, 152,
	38, 45, 35,
	165, 167, 169,
	169, 167, 168,
	165, 461, 167,
	166, 40, 170,
	170, 40, 168,
	165, 39, 37,
	42, 168, 40,
	160, 45, 43,
	173, 162, 163,
	172, 161, 162,
	174, 384, 175,
	177, 179, 176,
	153, 383, 179,
	149, 153, 179,
	149, 145, 152,
	185, 183, 182,
	183, 186, 483,
	483, 187, 200,
	390, 182, 184,
	186, 189, 483,
	187, 190, 200,
	192, 191, 183,
	192, 193, 191,
	397, 193, 192,
	397, 194, 193,
	189, 195, 196,
	196, 194, 198,
	194, 400, 198,
	197, 198, 68,
	187, 197, 199,
	199, 197, 68,
	68, 69, 199,
	70, 199, 69,
	190, 187, 199,
	202, 390, 184,
	188, 202, 184,
	203, 67, 215,
	67, 490, 204,
	204, 206, 205,
	204, 207, 208,
	207, 209, 208,
	206, 204, 210,
	210, 208, 214,
	214, 211, 210,
	71, 206, 201,
	206, 211, 201,
	490, 188, 200,
	208, 209, 214,
	209, 212, 213,
	214, 213, 211,
	213, 212, 211,
	184, 182, 181,
	212, 201, 211,
	71, 201, 70,
	212, 200, 201,
	153, 149, 152,
	44, 42, 32,
	44, 43, 42,
	222, 216, 217,
	219, 221, 8,
	218, 221, 219,
	5, 6, 220,
	4, 7, 221,
	9, 4, 218,
	220, 223, 222,
	222, 8, 220,
	225, 226, 227,
	228, 227, 226,
	229, 227, 228,
	230, 229, 228,
	231, 230, 228,
	24, 232, 228,
	24, 226, 225,
	225, 233, 24,
	231, 23, 235,
	24, 19, 232,
	226, 24, 228,
	237, 236, 468,
	241, 240, 239,
	238, 240, 241,
	242, 243, 244,
	247, 250, 248,
	250, 371, 246,
	250, 251, 371,
	253, 252, 242,
	253, 243, 252,
	247, 249, 254,
	251, 247, 254,
	256, 260, 266,
	256, 257, 241,
	237, 256, 236,
	261, 266, 260,
	259, 261, 260,
	238, 262, 255,
	258, 263, 262,
	263, 259, 255,
	216, 264, 259,
	261, 265, 266,
	266, 265, 267,
	269, 270, 271,
	273, 274, 275,
	269, 407, 215,
	276, 405, 277,
	275, 278, 279,
	273, 279, 280,
	272, 280, 410,
	269, 410, 407,
	276, 220, 6,
	59, 72, 281,
	270, 281, 282,
	275, 283, 223,
	269, 281, 270,
	271, 270, 282,
	273, 282, 274,
	275, 223, 276,
	275, 276, 277,
	283, 222, 223,
	216, 222, 224,
	285, 283, 286,
	287, 286, 284,
	282, 284, 286,
	286, 288, 285,
	224, 285, 216,
	290, 216, 285,
	290, 285, 288,
	291, 288, 287,
	293, 287, 284,
	294, 284, 281,
	295, 281, 72,
	90, 311, 296,
	299, 300, 301,
	300, 302, 303,
	302, 304, 303,
	305, 307, 306,
	307, 309, 308,
	313, 314, 315,
	314, 316, 317,
	316, 318, 304,
	318, 319, 320,
	319, 321, 320,
	321, 322, 307,
	322, 323, 309,
	323, 229, 230,
	324, 325, 314,
	325, 326, 316,
	330, 331, 332,
	331, 333, 332,
	289, 334, 265,
	291, 335, 290,
	289, 264, 216,
	289, 265, 261,
	289, 261, 264,
	263, 258, 9,
	9, 218, 263,
	265, 334, 268,
	90, 295, 85,
	23, 9, 336,
	310, 336, 267,
	308, 267, 268,
	306, 268, 334,
	305, 334, 290,
	303, 290, 335,
	303, 335, 292,
	301, 292, 293,
	297, 298, 293,
	297, 293, 294,
	296, 294, 295,
	311, 312, 297,
	312, 315, 300,
	315, 317, 302,
	304, 320, 305,
	309, 230, 310,
	230, 231, 234,
	316, 326, 318,
	326, 327, 318,
	327, 329, 321,
	329, 330, 322,
	330, 332, 322,
	332, 227, 229,
	337, 338, 328,
	338, 339, 330,
	339, 340, 331,
	340, 341, 333,
	132, 342, 324,
	342, 343, 324,
	343, 344, 325,
	344, 337, 326,
	339, 345, 340,
	345, 346, 340,
	332, 333, 227,
	347, 348, 337,
	338, 345, 339,
	132, 350, 342,
	350, 351, 343,
	351, 352, 344,
	352, 353, 347,
	348, 354, 338,
	354, 355, 349,
	351, 356, 352,
	356, 357, 353,
	357, 358, 348,
	358, 359, 354,
	355, 245, 242,
	153, 360, 361,
	360, 362, 361,
	362, 365, 363,
	365, 366, 359,
	366, 248, 359,
	161, 367, 360,
	367, 368, 362,
	368, 369, 365,
	369, 377, 366,
	359, 355, 354,
	363, 357, 356,
	361, 356, 351,
	361, 351, 350,
	364, 250, 246,
	364, 248, 250,
	243, 242, 252,
	375, 371, 477,
	372, 370, 374,
	370, 251, 374,
	375, 373, 376,
	253, 376, 374,
	375, 376, 253,
	246, 371, 375,
	251, 370, 371,
	368, 378, 379,
	368, 379, 369,
	378, 368, 173,
	367, 161, 172,
	367, 172, 173,
	174, 380, 178,
	176, 381, 177,
	382, 380, 174,
	380, 381, 176,
	382, 383, 380,
	383, 153, 381,
	384, 179, 180,
	350, 177, 381,
	381, 361, 350,
	391, 387, 385,
	391, 385, 392,
	389, 185, 390,
	393, 389, 387,
	392, 385, 388,
	391, 393, 387,
	393, 394, 389,
	394, 192, 185,
	399, 396, 393,
	396, 397, 394,
	402, 396, 399,
	400, 402, 399,
	401, 400, 399,
	400, 194, 402,
	68, 198, 400,
	277, 403, 278,
	404, 395, 279,
	279, 395, 280,
	202, 203, 406,
	390, 406, 388,
	203, 407, 406,
	407, 203, 215,
	410, 409, 407,
	409, 415, 408,
	412, 409, 411,
	414, 413, 412,
	280, 414, 411,
	414, 412, 411,
	388, 408, 392,
	392, 408, 416,
	416, 408, 415,
	416, 415, 417,
	386, 390, 388,
	280, 416, 414,
	280, 392, 416,
	361, 381, 153,
	4, 2, 7,
	7, 5, 8,
	14, 15, 13,
	17, 16, 15,
	19, 16, 17,
	18, 22, 23,
	19, 18, 231,
	20, 13, 24,
	452, 28, 25,
	27, 452, 26,
	30, 31, 28,
	28, 31, 25,
	452, 27, 29,
	151, 33, 32,
	34, 151, 41,
	43, 45, 38,
	38, 37, 39,
	42, 41, 32,
	42, 43, 36,
	39, 36, 38,
	26, 48, 51,
	25, 48, 26,
	25, 49, 48,
	25, 54, 49,
	54, 50, 49,
	46, 26, 51,
	53, 54, 30,
	30, 54, 25,
	54, 53, 3,
	53, 46, 47,
	53, 27, 46,
	3, 47, 0,
	47, 51, 52,
	52, 56, 57,
	49, 58, 56,
	62, 66, 64,
	59, 215, 67,
	66, 69, 68,
	62, 70, 69,
	61, 205, 71,
	59, 67, 205,
	64, 75, 74,
	64, 11, 75,
	65, 10, 11,
	65, 6, 10,
	61, 73, 60,
	62, 63, 73,
	65, 68, 405,
	65, 66, 68,
	60, 59, 61,
	76, 75, 12,
	75, 77, 78,
	11, 12, 75,
	74, 78, 80,
	60, 79, 72,
	73, 80, 79,
	78, 82, 80,
	77, 76, 82,
	85, 72, 79,
	127, 76, 81,
	86, 82, 76,
	87, 80, 82,
	85, 79, 80,
	90, 91, 89,
	91, 93, 92,
	95, 96, 94,
	96, 98, 97,
	98, 101, 100,
	89, 92, 104,
	105, 94, 107,
	94, 109, 108,
	109, 99, 110,
	99, 100, 111,
	100, 113, 112,
	113, 17, 15,
	104, 106, 116,
	106, 107, 117,
	119, 121, 120,
	121, 123, 122,
	88, 125, 85,
	87, 126, 125,
	87, 86, 126,
	83, 0, 55,
	50, 22, 128,
	21, 128, 22,
	102, 58, 128,
	98, 129, 58,
	98, 124, 129,
	98, 84, 124,
	96, 127, 84,
	96, 86, 127,
	95, 126, 86,
	91, 125, 126,
	90, 85, 125,
	93, 94, 105,
	96, 97, 109,
	100, 101, 113,
	101, 102, 113,
	102, 21, 17,
	89, 104, 114,
	108, 109, 118,
	109, 110, 119,
	110, 111, 121,
	111, 112, 123,
	117, 118, 136,
	118, 119, 137,
	119, 120, 130,
	120, 122, 131,
	89, 114, 133,
	114, 115, 135,
	130, 131, 138,
	15, 139, 122,
	122, 139, 131,
	135, 115, 140,
	115, 136, 140,
	136, 137, 141,
	137, 130, 142,
	130, 138, 143,
	132, 133, 145,
	133, 134, 145,
	134, 135, 146,
	135, 140, 147,
	141, 137, 148,
	137, 142, 148,
	143, 144, 151,
	140, 141, 147,
	141, 148, 150,
	142, 143, 151,
	157, 35, 160,
	153, 152, 158,
	155, 156, 159,
	156, 157, 160,
	158, 154, 161,
	154, 159, 162,
	159, 160, 163,
	157, 142, 151,
	157, 148, 142,
	156, 150, 148,
	155, 147, 150,
	155, 146, 147,
	152, 145, 146,
	33, 151, 144,
	35, 34, 38,
	151, 34, 35,
	40, 461, 165,
	461, 40, 166,
	39, 169, 168,
	39, 165, 169,
	37, 40, 165,
	168, 42, 39,
	40, 41, 42,
	43, 164, 160,
	163, 171, 173,
	162, 173, 172,
	384, 174, 178,
	178, 176, 179,
	384, 178, 179,
	179, 177, 149,
	180, 179, 383,
	483, 182, 183,
	200, 181, 483,
	200, 188, 181,
	182, 390, 185,
	187, 483, 189,
	183, 185, 192,
	186, 183, 191,
	189, 186, 191,
	195, 189, 191,
	195, 193, 194,
	195, 191, 193,
	198, 197, 196,
	197, 189, 196,
	197, 187, 189,
	199, 70, 190,
	70, 200, 190,
	70, 201, 200,
	67, 203, 491,
	205, 67, 204,
	204, 490, 207,
	208, 210, 204,
	206, 71, 205,
	211, 206, 210,
	212, 207, 490,
	212, 209, 207,
	200, 212, 490,
	213, 214, 209,
	181, 188, 184,
	216, 218, 217,
	218, 219, 217,
	219, 8, 217,
	217, 8, 222,
	220, 8, 5,
	8, 221, 7,
	221, 218, 4,
	228, 232, 231,
	231, 235, 234,
	231, 232, 19,
	24, 233, 20,
	256, 239, 236,
	239, 240, 236,
	245, 364, 246,
	248, 249, 247,
	375, 242, 246,
	242, 245, 246,
	242, 375, 253,
	243, 253, 254,
	254, 253, 251,
	247, 251, 250,
	266, 257, 256,
	258, 257, 266,
	258, 241, 257,
	255, 237, 238,
	260, 255, 259,
	260, 237, 255,
	256, 237, 260,
	241, 239, 256,
	241, 262, 238,
	262, 241, 258,
	255, 262, 263,
	259, 218, 216,
	261, 259, 264,
	259, 263, 218,
	267, 258, 266,
	268, 267, 265,
	215, 59, 269,
	278, 275, 277,
	279, 273, 275,
	280, 272, 273,
	410, 269, 271,
	283, 274, 282,
	283, 275, 274,
	220, 276, 223,
	281, 269, 59,
	282, 272, 271,
	282, 273, 272,
	410, 271, 272,
	283, 285, 224,
	224, 222, 283,
	286, 283, 282,
	284, 282, 281,
	288, 286, 287,
	216, 290, 289,
	288, 291, 290,
	287, 292, 291,
	287, 293, 292,
	284, 294, 293,
	281, 295, 294,
	297, 296, 311,
	301, 298, 299,
	303, 301, 300,
	305, 303, 304,
	308, 306, 307,
	310, 308, 309,
	311, 90, 103,
	315, 312, 313,
	317, 315, 314,
	304, 317, 316,
	320, 304, 318,
	307, 320, 321,
	309, 307, 322,
	230, 309, 323,
	312, 103, 324,
	313, 312, 324,
	314, 313, 324,
	316, 314, 325,
	329, 327, 328,
	330, 329, 328,
	295, 72, 85,
	335, 291, 292,
	334, 289, 290,
	336, 258, 267,
	9, 258, 336,
	336, 235, 23,
	336, 234, 235,
	336, 310, 234,
	267, 308, 310,
	268, 306, 308,
	334, 305, 306,
	290, 303, 305,
	292, 301, 303,
	293, 298, 301,
	294, 296, 297,
	295, 90, 296,
	298, 297, 312,
	299, 298, 312,
	300, 299, 312,
	302, 300, 315,
	304, 302, 317,
	307, 305, 320,
	234, 310, 230,
	312, 311, 103,
	319, 318, 327,
	321, 319, 327,
	322, 321, 329,
	323, 322, 332,
	229, 323, 332,
	327, 326, 337,
	328, 327, 337,
	330, 328, 338,
	331, 330, 339,
	333, 331, 340,
	324, 103, 132,
	325, 324, 343,
	326, 325, 344,
	341, 340, 346,
	337, 344, 347,
	338, 337, 348,
	346, 345, 349,
	343, 342, 350,
	344, 343, 351,
	347, 344, 352,
	348, 347, 353,
	345, 338, 354,
	349, 345, 354,
	346, 349, 355,
	350, 132, 177,
	353, 352, 356,
	348, 353, 357,
	354, 348, 358,
	363, 361, 362,
	360, 153, 158,
	358, 363, 365,
	359, 358, 365,
	364, 359, 248,
	360, 158, 161,
	362, 360, 367,
	365, 362, 368,
	366, 365, 369,
	355, 359, 364,
	357, 363, 358,
	356, 361, 363,
	355, 244, 346,
	355, 242, 244,
	245, 355, 364,
	370, 477, 371,
	477, 474, 375,
	474, 373, 375,
	374, 376, 372,
	370, 372, 477,
	374, 251, 253,
	377, 249, 248,
	377, 248, 366,
	173, 368, 367,
	176, 178, 380,
	174, 175, 382,
	381, 380, 383,
	383, 382, 180,
	388, 385, 386,
	389, 386, 387,
	390, 386, 389,
	185, 389, 394,
	394, 393, 396,
	192, 394, 397,
	397, 396, 398,
	398, 402, 397,
	393, 401, 399,
	403, 405, 400,
	400, 405, 68,
	401, 403, 400,
	391, 404, 401,
	404, 278, 401,
	403, 277, 405,
	278, 403, 401,
	279, 278, 404,
	392, 395, 391,
	406, 390, 202,
	407, 409, 408,
	409, 410, 411,
	412, 413, 409,
	409, 413, 415,
	280, 411, 410,
	413, 417, 415,
	413, 414, 417,
	280, 395, 392,
	417, 414, 416,
	393, 391, 401,
	404, 391, 395,
	144, 138, 131,
	144, 131, 139,
	418, 144, 139,
	14, 139, 15,
	418, 14, 20,
	233, 419, 420,
	33, 418, 422,
	421, 432, 32,
	423, 421, 425,
	422, 426, 425,
	426, 420, 419,
	171, 163, 429,
	163, 430, 428,
	430, 43, 427,
	163, 164, 430,
	430, 164, 43,
	433, 434, 420,
	426, 433, 420,
	423, 431, 421,
	434, 433, 426,
	432, 431, 423,
	32, 432, 423,
	341, 346, 244,
	333, 341, 435,
	437, 333, 435,
	227, 333, 225,
	435, 439, 437,
	436, 244, 243,
	435, 436, 439,
	442, 441, 424,
	438, 442, 425,
	439, 440, 419,
	443, 254, 249,
	444, 379, 429,
	443, 444, 428,
	254, 443, 427,
	243, 254, 44,
	445, 369, 444,
	249, 445, 443,
	445, 377, 369,
	249, 377, 445,
	173, 171, 379,
	446, 447, 439,
	447, 446, 440,
	418, 33, 144,
	14, 418, 139,
	420, 20, 233,
	20, 420, 418,
	421, 32, 33,
	422, 421, 33,
	418, 420, 422,
	424, 44, 423,
	425, 424, 423,
	422, 425, 421,
	419, 425, 426,
	44, 427, 43,
	428, 429, 163,
	427, 428, 430,
	422, 420, 434,
	426, 422, 434,
	432, 421, 431,
	423, 44, 32,
	244, 435, 341,
	436, 435, 244,
	437, 225, 333,
	437, 233, 225,
	233, 439, 419,
	439, 233, 437,
	243, 438, 436,
	438, 439, 436,
	439, 438, 440,
	438, 243, 441,
	243, 424, 441,
	424, 425, 442,
	438, 425, 440,
	425, 419, 440,
	444, 369, 379,
	379, 171, 429,
	429, 428, 444,
	428, 427, 443,
	427, 44, 254,
	44, 424, 243,
	444, 443, 445,
	379, 378, 173,
	439, 440, 446,
	440, 439, 447,
	438, 441, 448,
	441, 442, 448,
	442, 438, 448,
	29, 450, 449,
	451, 452, 29,
	29, 27, 453,
	454, 455, 30,
	450, 29, 453,
	456, 453, 27,
	453, 456, 455,
	451, 449, 455,
	457, 459, 458,
	460, 461, 457,
	461, 166, 457,
	462, 463, 168,
	459, 457, 166,
	166, 170, 464,
	464, 170, 463,
	460, 458, 463,
	466, 465, 467,
	468, 469, 467,
	238, 237, 465,
	240, 471, 470,
	472, 470, 471,
	238, 465, 466,
	473, 238, 466,
	471, 240, 473,
	473, 240, 238,
	467, 469, 472,
	465, 237, 468,
	466, 467, 472,
	475, 474, 476,
	477, 478, 476,
	376, 480, 479,
	481, 479, 480,
	373, 474, 475,
	482, 373, 475,
	480, 376, 482,
	482, 376, 373,
	476, 478, 481,
	475, 476, 481,
	29, 449, 451,
	455, 454, 451,
	454, 28, 451,
	30, 28, 454,
	451, 28, 452,
	27, 30, 456,
	456, 30, 455,
	455, 450, 453,
	450, 455, 449,
	457, 458, 460,
	463, 462, 460,
	462, 167, 460,
	168, 167, 462,
	460, 167, 461,
	464, 459, 166,
	170, 168, 463,
	463, 459, 464,
	459, 463, 458,
	468, 467, 465,
	236, 470, 469,
	470, 472, 469,
	470, 236, 240,
	471, 473, 472,
	236, 469, 468,
	466, 472, 473,
	477, 476, 474,
	372, 479, 478,
	479, 481, 478,
	479, 372, 376,
	480, 482, 481,
	372, 478, 477,
	475, 481, 482,
	195, 194, 196,
	181, 182, 483,
	385, 387, 386,
	402, 194, 397,
	398, 396, 402,
	202, 188, 484,
	484, 188, 486,
	188, 490, 488,
	488, 487, 489,
	487, 491, 484,
	489, 487, 485,
	486, 489, 485,
	388, 406, 492,
	494, 388, 493,
	408, 388, 494,
	496, 494, 495,
	498, 496, 497,
	495, 498, 497,
	498, 492, 496,
	408, 492, 407,
	492, 498, 493,
	495, 493, 498,
	202, 484, 203,
	486, 485, 484,
	485, 487, 484,
	488, 486, 188,
	488, 489, 486,
	488, 490, 491,
	67, 491, 490,
	487, 488, 491,
	203, 484, 491,
	492, 493, 388,
	493, 495, 494,
	494, 496, 408,
	495, 497, 496,
	408, 496, 492,
	492, 406, 407,
	500, 499, 501,
	382, 502, 499,
	499, 502, 501,
	502, 503, 501,
	382, 504, 502,
	502, 504, 505,
	502, 505, 506,
	502, 506, 503,
	504, 507, 505,
	507, 384, 508,
	507, 508, 505,
	505, 508, 506,
	508, 509, 506,
	384, 510, 511,
	384, 511, 508,
	508, 511, 512,
	508, 512, 509,
	512, 513, 509,
	509, 513, 506,
	175, 507, 504,
	175, 504, 382,
	384, 180, 510,
	175, 384, 507,
	500, 510, 180,
	500, 382, 499,
	511, 510, 500,
	512, 501, 513,
	511, 500, 501,
	512, 511, 501,
	501, 503, 513,
	506, 513, 503,
	500, 180, 382
	}
};
