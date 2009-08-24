/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2009 Michael Giacomelli
 *
 * 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#ifdef ROCKBOX
#include <codecs/lib/codeclib.h>
#else
#include <stdlib.h>
#include <stdint.h>
#endif /* ROCKBOX */

/* {sin(2*i*PI/4096, cos(2*i*PI/4096)}, with i = 0 to 512 */
const int32_t sincos_lookup0[1026] ICONST_ATTR = {
  0x00000000, 0x7fffffff, 0x003243f5, 0x7ffff621,
  0x006487e3, 0x7fffd886, 0x0096cbc1, 0x7fffa72c,
  0x00c90f88, 0x7fff6216, 0x00fb5330, 0x7fff0943,
  0x012d96b1, 0x7ffe9cb2, 0x015fda03, 0x7ffe1c65,
  0x01921d20, 0x7ffd885a, 0x01c45ffe, 0x7ffce093,
  0x01f6a297, 0x7ffc250f, 0x0228e4e2, 0x7ffb55ce,
  0x025b26d7, 0x7ffa72d1, 0x028d6870, 0x7ff97c18,
  0x02bfa9a4, 0x7ff871a2, 0x02f1ea6c, 0x7ff75370,
  0x03242abf, 0x7ff62182, 0x03566a96, 0x7ff4dbd9,
  0x0388a9ea, 0x7ff38274, 0x03bae8b2, 0x7ff21553,
  0x03ed26e6, 0x7ff09478, 0x041f6480, 0x7feeffe1,
  0x0451a177, 0x7fed5791, 0x0483ddc3, 0x7feb9b85,
  0x04b6195d, 0x7fe9cbc0, 0x04e8543e, 0x7fe7e841,
  0x051a8e5c, 0x7fe5f108, 0x054cc7b1, 0x7fe3e616,
  0x057f0035, 0x7fe1c76b, 0x05b137df, 0x7fdf9508,
  0x05e36ea9, 0x7fdd4eec, 0x0615a48b, 0x7fdaf519,
  0x0647d97c, 0x7fd8878e, 0x067a0d76, 0x7fd6064c,
  0x06ac406f, 0x7fd37153, 0x06de7262, 0x7fd0c8a3,
  0x0710a345, 0x7fce0c3e, 0x0742d311, 0x7fcb3c23,
  0x077501be, 0x7fc85854, 0x07a72f45, 0x7fc560cf,
  0x07d95b9e, 0x7fc25596, 0x080b86c2, 0x7fbf36aa,
  0x083db0a7, 0x7fbc040a, 0x086fd947, 0x7fb8bdb8,
  0x08a2009a, 0x7fb563b3, 0x08d42699, 0x7fb1f5fc,
  0x09064b3a, 0x7fae7495, 0x09386e78, 0x7faadf7c,
  0x096a9049, 0x7fa736b4, 0x099cb0a7, 0x7fa37a3c,
  0x09cecf89, 0x7f9faa15, 0x0a00ece8, 0x7f9bc640,
  0x0a3308bd, 0x7f97cebd, 0x0a6522fe, 0x7f93c38c,
  0x0a973ba5, 0x7f8fa4b0, 0x0ac952aa, 0x7f8b7227,
  0x0afb6805, 0x7f872bf3, 0x0b2d7baf, 0x7f82d214,
  0x0b5f8d9f, 0x7f7e648c, 0x0b919dcf, 0x7f79e35a,
  0x0bc3ac35, 0x7f754e80, 0x0bf5b8cb, 0x7f70a5fe,
  0x0c27c389, 0x7f6be9d4, 0x0c59cc68, 0x7f671a05,
  0x0c8bd35e, 0x7f62368f, 0x0cbdd865, 0x7f5d3f75,
  0x0cefdb76, 0x7f5834b7, 0x0d21dc87, 0x7f531655,
  0x0d53db92, 0x7f4de451, 0x0d85d88f, 0x7f489eaa,
  0x0db7d376, 0x7f434563, 0x0de9cc40, 0x7f3dd87c,
  0x0e1bc2e4, 0x7f3857f6, 0x0e4db75b, 0x7f32c3d1,
  0x0e7fa99e, 0x7f2d1c0e, 0x0eb199a4, 0x7f2760af,
  0x0ee38766, 0x7f2191b4, 0x0f1572dc, 0x7f1baf1e,
  0x0f475bff, 0x7f15b8ee, 0x0f7942c7, 0x7f0faf25,
  0x0fab272b, 0x7f0991c4, 0x0fdd0926, 0x7f0360cb,
  0x100ee8ad, 0x7efd1c3c, 0x1040c5bb, 0x7ef6c418,
  0x1072a048, 0x7ef05860, 0x10a4784b, 0x7ee9d914,
  0x10d64dbd, 0x7ee34636, 0x11082096, 0x7edc9fc6,
  0x1139f0cf, 0x7ed5e5c6, 0x116bbe60, 0x7ecf1837,
  0x119d8941, 0x7ec8371a, 0x11cf516a, 0x7ec14270,
  0x120116d5, 0x7eba3a39, 0x1232d979, 0x7eb31e78,
  0x1264994e, 0x7eabef2c, 0x1296564d, 0x7ea4ac58,
  0x12c8106f, 0x7e9d55fc, 0x12f9c7aa, 0x7e95ec1a,
  0x132b7bf9, 0x7e8e6eb2, 0x135d2d53, 0x7e86ddc6,
  0x138edbb1, 0x7e7f3957, 0x13c0870a, 0x7e778166,
  0x13f22f58, 0x7e6fb5f4, 0x1423d492, 0x7e67d703,
  0x145576b1, 0x7e5fe493, 0x148715ae, 0x7e57dea7,
  0x14b8b17f, 0x7e4fc53e, 0x14ea4a1f, 0x7e47985b,
  0x151bdf86, 0x7e3f57ff, 0x154d71aa, 0x7e37042a,
  0x157f0086, 0x7e2e9cdf, 0x15b08c12, 0x7e26221f,
  0x15e21445, 0x7e1d93ea, 0x16139918, 0x7e14f242,
  0x16451a83, 0x7e0c3d29, 0x1676987f, 0x7e0374a0,
  0x16a81305, 0x7dfa98a8, 0x16d98a0c, 0x7df1a942,
  0x170afd8d, 0x7de8a670, 0x173c6d80, 0x7ddf9034,
  0x176dd9de, 0x7dd6668f, 0x179f429f, 0x7dcd2981,
  0x17d0a7bc, 0x7dc3d90d, 0x1802092c, 0x7dba7534,
  0x183366e9, 0x7db0fdf8, 0x1864c0ea, 0x7da77359,
  0x18961728, 0x7d9dd55a, 0x18c7699b, 0x7d9423fc,
  0x18f8b83c, 0x7d8a5f40, 0x192a0304, 0x7d808728,
  0x195b49ea, 0x7d769bb5, 0x198c8ce7, 0x7d6c9ce9,
  0x19bdcbf3, 0x7d628ac6, 0x19ef0707, 0x7d58654d,
  0x1a203e1b, 0x7d4e2c7f, 0x1a517128, 0x7d43e05e,
  0x1a82a026, 0x7d3980ec, 0x1ab3cb0d, 0x7d2f0e2b,
  0x1ae4f1d6, 0x7d24881b, 0x1b161479, 0x7d19eebf,
  0x1b4732ef, 0x7d0f4218, 0x1b784d30, 0x7d048228,
  0x1ba96335, 0x7cf9aef0, 0x1bda74f6, 0x7ceec873,
  0x1c0b826a, 0x7ce3ceb2, 0x1c3c8b8c, 0x7cd8c1ae,
  0x1c6d9053, 0x7ccda169, 0x1c9e90b8, 0x7cc26de5,
  0x1ccf8cb3, 0x7cb72724, 0x1d00843d, 0x7cabcd28,
  0x1d31774d, 0x7ca05ff1, 0x1d6265dd, 0x7c94df83,
  0x1d934fe5, 0x7c894bde, 0x1dc4355e, 0x7c7da505,
  0x1df5163f, 0x7c71eaf9, 0x1e25f282, 0x7c661dbc,
  0x1e56ca1e, 0x7c5a3d50, 0x1e879d0d, 0x7c4e49b7,
  0x1eb86b46, 0x7c4242f2, 0x1ee934c3, 0x7c362904,
  0x1f19f97b, 0x7c29fbee, 0x1f4ab968, 0x7c1dbbb3,
  0x1f7b7481, 0x7c116853, 0x1fac2abf, 0x7c0501d2,
  0x1fdcdc1b, 0x7bf88830, 0x200d888d, 0x7bebfb70,
  0x203e300d, 0x7bdf5b94, 0x206ed295, 0x7bd2a89e,
  0x209f701c, 0x7bc5e290, 0x20d0089c, 0x7bb9096b,
  0x21009c0c, 0x7bac1d31, 0x21312a65, 0x7b9f1de6,
  0x2161b3a0, 0x7b920b89, 0x219237b5, 0x7b84e61f,
  0x21c2b69c, 0x7b77ada8, 0x21f3304f, 0x7b6a6227,
  0x2223a4c5, 0x7b5d039e, 0x225413f8, 0x7b4f920e,
  0x22847de0, 0x7b420d7a, 0x22b4e274, 0x7b3475e5,
  0x22e541af, 0x7b26cb4f, 0x23159b88, 0x7b190dbc,
  0x2345eff8, 0x7b0b3d2c, 0x23763ef7, 0x7afd59a4,
  0x23a6887f, 0x7aef6323, 0x23d6cc87, 0x7ae159ae,
  0x24070b08, 0x7ad33d45, 0x243743fa, 0x7ac50dec,
  0x24677758, 0x7ab6cba4, 0x2497a517, 0x7aa8766f,
  0x24c7cd33, 0x7a9a0e50, 0x24f7efa2, 0x7a8b9348,
  0x25280c5e, 0x7a7d055b, 0x2558235f, 0x7a6e648a,
  0x2588349d, 0x7a5fb0d8, 0x25b84012, 0x7a50ea47,
  0x25e845b6, 0x7a4210d8, 0x26184581, 0x7a332490,
  0x26483f6c, 0x7a24256f, 0x26783370, 0x7a151378,
  0x26a82186, 0x7a05eead, 0x26d809a5, 0x79f6b711,
  0x2707ebc7, 0x79e76ca7, 0x2737c7e3, 0x79d80f6f,
  0x27679df4, 0x79c89f6e, 0x27976df1, 0x79b91ca4,
  0x27c737d3, 0x79a98715, 0x27f6fb92, 0x7999dec4,
  0x2826b928, 0x798a23b1, 0x2856708d, 0x797a55e0,
  0x288621b9, 0x796a7554, 0x28b5cca5, 0x795a820e,
  0x28e5714b, 0x794a7c12, 0x29150fa1, 0x793a6361,
  0x2944a7a2, 0x792a37fe, 0x29743946, 0x7919f9ec,
  0x29a3c485, 0x7909a92d, 0x29d34958, 0x78f945c3,
  0x2a02c7b8, 0x78e8cfb2, 0x2a323f9e, 0x78d846fb,
  0x2a61b101, 0x78c7aba2, 0x2a911bdc, 0x78b6fda8,
  0x2ac08026, 0x78a63d11, 0x2aefddd8, 0x789569df,
  0x2b1f34eb, 0x78848414, 0x2b4e8558, 0x78738bb3,
  0x2b7dcf17, 0x786280bf, 0x2bad1221, 0x7851633b,
  0x2bdc4e6f, 0x78403329, 0x2c0b83fa, 0x782ef08b,
  0x2c3ab2b9, 0x781d9b65, 0x2c69daa6, 0x780c33b8,
  0x2c98fbba, 0x77fab989, 0x2cc815ee, 0x77e92cd9,
  0x2cf72939, 0x77d78daa, 0x2d263596, 0x77c5dc01,
  0x2d553afc, 0x77b417df, 0x2d843964, 0x77a24148,
  0x2db330c7, 0x7790583e, 0x2de2211e, 0x777e5cc3,
  0x2e110a62, 0x776c4edb, 0x2e3fec8b, 0x775a2e89,
  0x2e6ec792, 0x7747fbce, 0x2e9d9b70, 0x7735b6af,
  0x2ecc681e, 0x77235f2d, 0x2efb2d95, 0x7710f54c,
  0x2f29ebcc, 0x76fe790e, 0x2f58a2be, 0x76ebea77,
  0x2f875262, 0x76d94989, 0x2fb5fab2, 0x76c69647,
  0x2fe49ba7, 0x76b3d0b4, 0x30133539, 0x76a0f8d2,
  0x3041c761, 0x768e0ea6, 0x30705217, 0x767b1231,
  0x309ed556, 0x76680376, 0x30cd5115, 0x7654e279,
  0x30fbc54d, 0x7641af3d, 0x312a31f8, 0x762e69c4,
  0x3158970e, 0x761b1211, 0x3186f487, 0x7607a828,
  0x31b54a5e, 0x75f42c0b, 0x31e39889, 0x75e09dbd,
  0x3211df04, 0x75ccfd42, 0x32401dc6, 0x75b94a9c,
  0x326e54c7, 0x75a585cf, 0x329c8402, 0x7591aedd,
  0x32caab6f, 0x757dc5ca, 0x32f8cb07, 0x7569ca99,
  0x3326e2c3, 0x7555bd4c, 0x3354f29b, 0x75419de7,
  0x3382fa88, 0x752d6c6c, 0x33b0fa84, 0x751928e0,
  0x33def287, 0x7504d345, 0x340ce28b, 0x74f06b9e,
  0x343aca87, 0x74dbf1ef, 0x3468aa76, 0x74c7663a,
  0x34968250, 0x74b2c884, 0x34c4520d, 0x749e18cd,
  0x34f219a8, 0x7489571c, 0x351fd918, 0x74748371,
  0x354d9057, 0x745f9dd1, 0x357b3f5d, 0x744aa63f,
  0x35a8e625, 0x74359cbd, 0x35d684a6, 0x74208150,
  0x36041ad9, 0x740b53fb, 0x3631a8b8, 0x73f614c0,
  0x365f2e3b, 0x73e0c3a3, 0x368cab5c, 0x73cb60a8,
  0x36ba2014, 0x73b5ebd1, 0x36e78c5b, 0x73a06522,
  0x3714f02a, 0x738acc9e, 0x37424b7b, 0x73752249,
  0x376f9e46, 0x735f6626, 0x379ce885, 0x73499838,
  0x37ca2a30, 0x7333b883, 0x37f76341, 0x731dc70a,
  0x382493b0, 0x7307c3d0, 0x3851bb77, 0x72f1aed9,
  0x387eda8e, 0x72db8828, 0x38abf0ef, 0x72c54fc1,
  0x38d8fe93, 0x72af05a7, 0x39060373, 0x7298a9dd,
  0x3932ff87, 0x72823c67, 0x395ff2c9, 0x726bbd48,
  0x398cdd32, 0x72552c85, 0x39b9bebc, 0x723e8a20,
  0x39e6975e, 0x7227d61c, 0x3a136712, 0x7211107e,
  0x3a402dd2, 0x71fa3949, 0x3a6ceb96, 0x71e35080,
  0x3a99a057, 0x71cc5626, 0x3ac64c0f, 0x71b54a41,
  0x3af2eeb7, 0x719e2cd2, 0x3b1f8848, 0x7186fdde,
  0x3b4c18ba, 0x716fbd68, 0x3b78a007, 0x71586b74,
  0x3ba51e29, 0x71410805, 0x3bd19318, 0x7129931f,
  0x3bfdfecd, 0x71120cc5, 0x3c2a6142, 0x70fa74fc,
  0x3c56ba70, 0x70e2cbc6, 0x3c830a50, 0x70cb1128,
  0x3caf50da, 0x70b34525, 0x3cdb8e09, 0x709b67c0,
  0x3d07c1d6, 0x708378ff, 0x3d33ec39, 0x706b78e3,
  0x3d600d2c, 0x70536771, 0x3d8c24a8, 0x703b44ad,
  0x3db832a6, 0x7023109a, 0x3de4371f, 0x700acb3c,
  0x3e10320d, 0x6ff27497, 0x3e3c2369, 0x6fda0cae,
  0x3e680b2c, 0x6fc19385, 0x3e93e950, 0x6fa90921,
  0x3ebfbdcd, 0x6f906d84, 0x3eeb889c, 0x6f77c0b3,
  0x3f1749b8, 0x6f5f02b2, 0x3f430119, 0x6f463383,
  0x3f6eaeb8, 0x6f2d532c, 0x3f9a5290, 0x6f1461b0,
  0x3fc5ec98, 0x6efb5f12, 0x3ff17cca, 0x6ee24b57,
  0x401d0321, 0x6ec92683, 0x40487f94, 0x6eaff099,
  0x4073f21d, 0x6e96a99d, 0x409f5ab6, 0x6e7d5193,
  0x40cab958, 0x6e63e87f, 0x40f60dfb, 0x6e4a6e66,
  0x4121589b, 0x6e30e34a, 0x414c992f, 0x6e174730,
  0x4177cfb1, 0x6dfd9a1c, 0x41a2fc1a, 0x6de3dc11,
  0x41ce1e65, 0x6dca0d14, 0x41f93689, 0x6db02d29,
  0x42244481, 0x6d963c54, 0x424f4845, 0x6d7c3a98,
  0x427a41d0, 0x6d6227fa, 0x42a5311b, 0x6d48047e,
  0x42d0161e, 0x6d2dd027, 0x42faf0d4, 0x6d138afb,
  0x4325c135, 0x6cf934fc, 0x4350873c, 0x6cdece2f,
  0x437b42e1, 0x6cc45698, 0x43a5f41e, 0x6ca9ce3b,
  0x43d09aed, 0x6c8f351c, 0x43fb3746, 0x6c748b3f,
  0x4425c923, 0x6c59d0a9, 0x4450507e, 0x6c3f055d,
  0x447acd50, 0x6c242960, 0x44a53f93, 0x6c093cb6,
  0x44cfa740, 0x6bee3f62, 0x44fa0450, 0x6bd3316a,
  0x452456bd, 0x6bb812d1, 0x454e9e80, 0x6b9ce39b,
  0x4578db93, 0x6b81a3cd, 0x45a30df0, 0x6b66536b,
  0x45cd358f, 0x6b4af279, 0x45f7526b, 0x6b2f80fb,
  0x4621647d, 0x6b13fef5, 0x464b6bbe, 0x6af86c6c,
  0x46756828, 0x6adcc964, 0x469f59b4, 0x6ac115e2,
  0x46c9405c, 0x6aa551e9, 0x46f31c1a, 0x6a897d7d,
  0x471cece7, 0x6a6d98a4, 0x4746b2bc, 0x6a51a361,
  0x47706d93, 0x6a359db9, 0x479a1d67, 0x6a1987b0,
  0x47c3c22f, 0x69fd614a, 0x47ed5be6, 0x69e12a8c,
  0x4816ea86, 0x69c4e37a, 0x48406e08, 0x69a88c19,
  0x4869e665, 0x698c246c, 0x48935397, 0x696fac78,
  0x48bcb599, 0x69532442, 0x48e60c62, 0x69368bce,
  0x490f57ee, 0x6919e320, 0x49389836, 0x68fd2a3d,
  0x4961cd33, 0x68e06129, 0x498af6df, 0x68c387e9,
  0x49b41533, 0x68a69e81, 0x49dd282a, 0x6889a4f6,
  0x4a062fbd, 0x686c9b4b, 0x4a2f2be6, 0x684f8186,
  0x4a581c9e, 0x683257ab, 0x4a8101de, 0x68151dbe,
  0x4aa9dba2, 0x67f7d3c5, 0x4ad2a9e2, 0x67da79c3,
  0x4afb6c98, 0x67bd0fbd, 0x4b2423be, 0x679f95b7,
  0x4b4ccf4d, 0x67820bb7, 0x4b756f40, 0x676471c0,
  0x4b9e0390, 0x6746c7d8, 0x4bc68c36, 0x67290e02,
  0x4bef092d, 0x670b4444, 0x4c177a6e, 0x66ed6aa1,
  0x4c3fdff4, 0x66cf8120, 0x4c6839b7, 0x66b187c3,
  0x4c9087b1, 0x66937e91, 0x4cb8c9dd, 0x6675658c,
  0x4ce10034, 0x66573cbb, 0x4d092ab0, 0x66390422,
  0x4d31494b, 0x661abbc5, 0x4d595bfe, 0x65fc63a9,
  0x4d8162c4, 0x65ddfbd3, 0x4da95d96, 0x65bf8447,
  0x4dd14c6e, 0x65a0fd0b, 0x4df92f46, 0x65826622,
  0x4e210617, 0x6563bf92, 0x4e48d0dd, 0x6545095f,
  0x4e708f8f, 0x6526438f, 0x4e984229, 0x65076e25,
  0x4ebfe8a5, 0x64e88926, 0x4ee782fb, 0x64c99498,
  0x4f0f1126, 0x64aa907f, 0x4f369320, 0x648b7ce0,
  0x4f5e08e3, 0x646c59bf, 0x4f857269, 0x644d2722,
  0x4faccfab, 0x642de50d, 0x4fd420a4, 0x640e9386,
  0x4ffb654d, 0x63ef3290, 0x50229da1, 0x63cfc231,
  0x5049c999, 0x63b0426d, 0x5070e92f, 0x6390b34a,
  0x5097fc5e, 0x637114cc, 0x50bf031f, 0x635166f9,
  0x50e5fd6d, 0x6331a9d4, 0x510ceb40, 0x6311dd64,
  0x5133cc94, 0x62f201ac, 0x515aa162, 0x62d216b3,
  0x518169a5, 0x62b21c7b, 0x51a82555, 0x6292130c,
  0x51ced46e, 0x6271fa69, 0x51f576ea, 0x6251d298,
  0x521c0cc2, 0x62319b9d, 0x524295f0, 0x6211557e,
  0x5269126e, 0x61f1003f, 0x528f8238, 0x61d09be5,
  0x52b5e546, 0x61b02876, 0x52dc3b92, 0x618fa5f7,
  0x53028518, 0x616f146c, 0x5328c1d0, 0x614e73da,
  0x534ef1b5, 0x612dc447, 0x537514c2, 0x610d05b7,
  0x539b2af0, 0x60ec3830, 0x53c13439, 0x60cb5bb7,
  0x53e73097, 0x60aa7050, 0x540d2005, 0x60897601,
  0x5433027d, 0x60686ccf, 0x5458d7f9, 0x604754bf,
  0x547ea073, 0x60262dd6, 0x54a45be6, 0x6004f819,
  0x54ca0a4b, 0x5fe3b38d, 0x54efab9c, 0x5fc26038,
  0x55153fd4, 0x5fa0fe1f, 0x553ac6ee, 0x5f7f8d46,
  0x556040e2, 0x5f5e0db3, 0x5585adad, 0x5f3c7f6b,
  0x55ab0d46, 0x5f1ae274, 0x55d05faa, 0x5ef936d1,
  0x55f5a4d2, 0x5ed77c8a, 0x561adcb9, 0x5eb5b3a2,
  0x56400758, 0x5e93dc1f, 0x566524aa, 0x5e71f606,
  0x568a34a9, 0x5e50015d, 0x56af3750, 0x5e2dfe29,
  0x56d42c99, 0x5e0bec6e, 0x56f9147e, 0x5de9cc33,
  0x571deefa, 0x5dc79d7c, 0x5742bc06, 0x5da5604f,
  0x57677b9d, 0x5d8314b1, 0x578c2dba, 0x5d60baa7,
  0x57b0d256, 0x5d3e5237, 0x57d5696d, 0x5d1bdb65,
  0x57f9f2f8, 0x5cf95638, 0x581e6ef1, 0x5cd6c2b5,
  0x5842dd54, 0x5cb420e0, 0x58673e1b, 0x5c9170bf,
  0x588b9140, 0x5c6eb258, 0x58afd6bd, 0x5c4be5b0,
  0x58d40e8c, 0x5c290acc, 0x58f838a9, 0x5c0621b2,
  0x591c550e, 0x5be32a67, 0x594063b5, 0x5bc024f0,
  0x59646498, 0x5b9d1154, 0x598857b2, 0x5b79ef96,
  0x59ac3cfd, 0x5b56bfbd, 0x59d01475, 0x5b3381ce,
  0x59f3de12, 0x5b1035cf, 0x5a1799d1, 0x5aecdbc5,
  0x5a3b47ab, 0x5ac973b5, 0x5a5ee79a, 0x5aa5fda5,
  0x5a82799a, 0x5a82799a
  };

  /* {sin((2*i+1)*PI/4096, cos((2*i+1)*PI/4096)}, with i = 0 to 511 */
const int32_t sincos_lookup1[1024] ICONST_ATTR = {
  0x001921fb, 0x7ffffd88, 0x004b65ee, 0x7fffe9cb,
  0x007da9d4, 0x7fffc251, 0x00afeda8, 0x7fff8719,
  0x00e23160, 0x7fff3824, 0x011474f6, 0x7ffed572,
  0x0146b860, 0x7ffe5f03, 0x0178fb99, 0x7ffdd4d7,
  0x01ab3e97, 0x7ffd36ee, 0x01dd8154, 0x7ffc8549,
  0x020fc3c6, 0x7ffbbfe6, 0x024205e8, 0x7ffae6c7,
  0x027447b0, 0x7ff9f9ec, 0x02a68917, 0x7ff8f954,
  0x02d8ca16, 0x7ff7e500, 0x030b0aa4, 0x7ff6bcf0,
  0x033d4abb, 0x7ff58125, 0x036f8a51, 0x7ff4319d,
  0x03a1c960, 0x7ff2ce5b, 0x03d407df, 0x7ff1575d,
  0x040645c7, 0x7fefcca4, 0x04388310, 0x7fee2e30,
  0x046abfb3, 0x7fec7c02, 0x049cfba7, 0x7feab61a,
  0x04cf36e5, 0x7fe8dc78, 0x05017165, 0x7fe6ef1c,
  0x0533ab20, 0x7fe4ee06, 0x0565e40d, 0x7fe2d938,
  0x05981c26, 0x7fe0b0b1, 0x05ca5361, 0x7fde7471,
  0x05fc89b8, 0x7fdc247a, 0x062ebf22, 0x7fd9c0ca,
  0x0660f398, 0x7fd74964, 0x06932713, 0x7fd4be46,
  0x06c5598a, 0x7fd21f72, 0x06f78af6, 0x7fcf6ce8,
  0x0729bb4e, 0x7fcca6a7, 0x075bea8c, 0x7fc9ccb2,
  0x078e18a7, 0x7fc6df08, 0x07c04598, 0x7fc3dda9,
  0x07f27157, 0x7fc0c896, 0x08249bdd, 0x7fbd9fd0,
  0x0856c520, 0x7fba6357, 0x0888ed1b, 0x7fb7132b,
  0x08bb13c5, 0x7fb3af4e, 0x08ed3916, 0x7fb037bf,
  0x091f5d06, 0x7facac7f, 0x09517f8f, 0x7fa90d8e,
  0x0983a0a7, 0x7fa55aee, 0x09b5c048, 0x7fa1949e,
  0x09e7de6a, 0x7f9dbaa0, 0x0a19fb04, 0x7f99ccf4,
  0x0a4c1610, 0x7f95cb9a, 0x0a7e2f85, 0x7f91b694,
  0x0ab0475c, 0x7f8d8de1, 0x0ae25d8d, 0x7f895182,
  0x0b147211, 0x7f850179, 0x0b4684df, 0x7f809dc5,
  0x0b7895f0, 0x7f7c2668, 0x0baaa53b, 0x7f779b62,
  0x0bdcb2bb, 0x7f72fcb4, 0x0c0ebe66, 0x7f6e4a5e,
  0x0c40c835, 0x7f698461, 0x0c72d020, 0x7f64aabf,
  0x0ca4d620, 0x7f5fbd77, 0x0cd6da2d, 0x7f5abc8a,
  0x0d08dc3f, 0x7f55a7fa, 0x0d3adc4e, 0x7f507fc7,
  0x0d6cda53, 0x7f4b43f2, 0x0d9ed646, 0x7f45f47b,
  0x0dd0d01f, 0x7f409164, 0x0e02c7d7, 0x7f3b1aad,
  0x0e34bd66, 0x7f359057, 0x0e66b0c3, 0x7f2ff263,
  0x0e98a1e9, 0x7f2a40d2, 0x0eca90ce, 0x7f247ba5,
  0x0efc7d6b, 0x7f1ea2dc, 0x0f2e67b8, 0x7f18b679,
  0x0f604faf, 0x7f12b67c, 0x0f923546, 0x7f0ca2e7,
  0x0fc41876, 0x7f067bba, 0x0ff5f938, 0x7f0040f6,
  0x1027d784, 0x7ef9f29d, 0x1059b352, 0x7ef390ae,
  0x108b8c9b, 0x7eed1b2c, 0x10bd6356, 0x7ee69217,
  0x10ef377d, 0x7edff570, 0x11210907, 0x7ed94538,
  0x1152d7ed, 0x7ed28171, 0x1184a427, 0x7ecbaa1a,
  0x11b66dad, 0x7ec4bf36, 0x11e83478, 0x7ebdc0c6,
  0x1219f880, 0x7eb6aeca, 0x124bb9be, 0x7eaf8943,
  0x127d7829, 0x7ea85033, 0x12af33ba, 0x7ea1039b,
  0x12e0ec6a, 0x7e99a37c, 0x1312a230, 0x7e922fd6,
  0x13445505, 0x7e8aa8ac, 0x137604e2, 0x7e830dff,
  0x13a7b1bf, 0x7e7b5fce, 0x13d95b93, 0x7e739e1d,
  0x140b0258, 0x7e6bc8eb, 0x143ca605, 0x7e63e03b,
  0x146e4694, 0x7e5be40c, 0x149fe3fc, 0x7e53d462,
  0x14d17e36, 0x7e4bb13c, 0x1503153a, 0x7e437a9c,
  0x1534a901, 0x7e3b3083, 0x15663982, 0x7e32d2f4,
  0x1597c6b7, 0x7e2a61ed, 0x15c95097, 0x7e21dd73,
  0x15fad71b, 0x7e194584, 0x162c5a3b, 0x7e109a24,
  0x165dd9f0, 0x7e07db52, 0x168f5632, 0x7dff0911,
  0x16c0cef9, 0x7df62362, 0x16f2443e, 0x7ded2a47,
  0x1723b5f9, 0x7de41dc0, 0x17552422, 0x7ddafdce,
  0x17868eb3, 0x7dd1ca75, 0x17b7f5a3, 0x7dc883b4,
  0x17e958ea, 0x7dbf298d, 0x181ab881, 0x7db5bc02,
  0x184c1461, 0x7dac3b15, 0x187d6c82, 0x7da2a6c6,
  0x18aec0db, 0x7d98ff17, 0x18e01167, 0x7d8f4409,
  0x19115e1c, 0x7d85759f, 0x1942a6f3, 0x7d7b93da,
  0x1973ebe6, 0x7d719eba, 0x19a52ceb, 0x7d679642,
  0x19d669fc, 0x7d5d7a74, 0x1a07a311, 0x7d534b50,
  0x1a38d823, 0x7d4908d9, 0x1a6a0929, 0x7d3eb30f,
  0x1a9b361d, 0x7d3449f5, 0x1acc5ef6, 0x7d29cd8c,
  0x1afd83ad, 0x7d1f3dd6, 0x1b2ea43a, 0x7d149ad5,
  0x1b5fc097, 0x7d09e489, 0x1b90d8bb, 0x7cff1af5,
  0x1bc1ec9e, 0x7cf43e1a, 0x1bf2fc3a, 0x7ce94dfb,
  0x1c240786, 0x7cde4a98, 0x1c550e7c, 0x7cd333f3,
  0x1c861113, 0x7cc80a0f, 0x1cb70f43, 0x7cbcccec,
  0x1ce80906, 0x7cb17c8d, 0x1d18fe54, 0x7ca618f3,
  0x1d49ef26, 0x7c9aa221, 0x1d7adb73, 0x7c8f1817,
  0x1dabc334, 0x7c837ad8, 0x1ddca662, 0x7c77ca65,
  0x1e0d84f5, 0x7c6c06c0, 0x1e3e5ee5, 0x7c602fec,
  0x1e6f342c, 0x7c5445e9, 0x1ea004c1, 0x7c4848ba,
  0x1ed0d09d, 0x7c3c3860, 0x1f0197b8, 0x7c3014de,
  0x1f325a0b, 0x7c23de35, 0x1f63178f, 0x7c179467,
  0x1f93d03c, 0x7c0b3777, 0x1fc4840a, 0x7bfec765,
  0x1ff532f2, 0x7bf24434, 0x2025dcec, 0x7be5ade6,
  0x205681f1, 0x7bd9047c, 0x208721f9, 0x7bcc47fa,
  0x20b7bcfe, 0x7bbf7860, 0x20e852f6, 0x7bb295b0,
  0x2118e3dc, 0x7ba59fee, 0x21496fa7, 0x7b989719,
  0x2179f64f, 0x7b8b7b36, 0x21aa77cf, 0x7b7e4c45,
  0x21daf41d, 0x7b710a49, 0x220b6b32, 0x7b63b543,
  0x223bdd08, 0x7b564d36, 0x226c4996, 0x7b48d225,
  0x229cb0d5, 0x7b3b4410, 0x22cd12bd, 0x7b2da2fa,
  0x22fd6f48, 0x7b1feee5, 0x232dc66d, 0x7b1227d3,
  0x235e1826, 0x7b044dc7, 0x238e646a, 0x7af660c2,
  0x23beab33, 0x7ae860c7, 0x23eeec78, 0x7ada4dd8,
  0x241f2833, 0x7acc27f7, 0x244f5e5c, 0x7abdef25,
  0x247f8eec, 0x7aafa367, 0x24afb9da, 0x7aa144bc,
  0x24dfdf20, 0x7a92d329, 0x250ffeb7, 0x7a844eae,
  0x25401896, 0x7a75b74f, 0x25702cb7, 0x7a670d0d,
  0x25a03b11, 0x7a584feb, 0x25d0439f, 0x7a497feb,
  0x26004657, 0x7a3a9d0f, 0x26304333, 0x7a2ba75a,
  0x26603a2c, 0x7a1c9ece, 0x26902b39, 0x7a0d836d,
  0x26c01655, 0x79fe5539, 0x26effb76, 0x79ef1436,
  0x271fda96, 0x79dfc064, 0x274fb3ae, 0x79d059c8,
  0x277f86b5, 0x79c0e062, 0x27af53a6, 0x79b15435,
  0x27df1a77, 0x79a1b545, 0x280edb23, 0x79920392,
  0x283e95a1, 0x79823f20, 0x286e49ea, 0x797267f2,
  0x289df7f8, 0x79627e08, 0x28cd9fc1, 0x79528167,
  0x28fd4140, 0x79427210, 0x292cdc6d, 0x79325006,
  0x295c7140, 0x79221b4b, 0x298bffb2, 0x7911d3e2,
  0x29bb87bc, 0x790179cd, 0x29eb0957, 0x78f10d0f,
  0x2a1a847b, 0x78e08dab, 0x2a49f920, 0x78cffba3,
  0x2a796740, 0x78bf56f9, 0x2aa8ced3, 0x78ae9fb0,
  0x2ad82fd2, 0x789dd5cb, 0x2b078a36, 0x788cf94c,
  0x2b36ddf7, 0x787c0a36, 0x2b662b0e, 0x786b088c,
  0x2b957173, 0x7859f44f, 0x2bc4b120, 0x7848cd83,
  0x2bf3ea0d, 0x7837942b, 0x2c231c33, 0x78264849,
  0x2c52478a, 0x7814e9df, 0x2c816c0c, 0x780378f1,
  0x2cb089b1, 0x77f1f581, 0x2cdfa071, 0x77e05f91,
  0x2d0eb046, 0x77ceb725, 0x2d3db928, 0x77bcfc3f,
  0x2d6cbb10, 0x77ab2ee2, 0x2d9bb5f6, 0x77994f11,
  0x2dcaa9d5, 0x77875cce, 0x2df996a3, 0x7775581d,
  0x2e287c5a, 0x776340ff, 0x2e575af3, 0x77511778,
  0x2e863267, 0x773edb8b, 0x2eb502ae, 0x772c8d3a,
  0x2ee3cbc1, 0x771a2c88, 0x2f128d99, 0x7707b979,
  0x2f41482e, 0x76f5340e, 0x2f6ffb7a, 0x76e29c4b,
  0x2f9ea775, 0x76cff232, 0x2fcd4c19, 0x76bd35c7,
  0x2ffbe95d, 0x76aa670d, 0x302a7f3a, 0x76978605,
  0x30590dab, 0x768492b4, 0x308794a6, 0x76718d1c,
  0x30b61426, 0x765e7540, 0x30e48c22, 0x764b4b23,
  0x3112fc95, 0x76380ec8, 0x31416576, 0x7624c031,
  0x316fc6be, 0x76115f63, 0x319e2067, 0x75fdec60,
  0x31cc7269, 0x75ea672a, 0x31fabcbd, 0x75d6cfc5,
  0x3228ff5c, 0x75c32634, 0x32573a3f, 0x75af6a7b,
  0x32856d5e, 0x759b9c9b, 0x32b398b3, 0x7587bc98,
  0x32e1bc36, 0x7573ca75, 0x330fd7e1, 0x755fc635,
  0x333debab, 0x754bafdc, 0x336bf78f, 0x7537876c,
  0x3399fb85, 0x75234ce8, 0x33c7f785, 0x750f0054,
  0x33f5eb89, 0x74faa1b3, 0x3423d78a, 0x74e63108,
  0x3451bb81, 0x74d1ae55, 0x347f9766, 0x74bd199f,
  0x34ad6b32, 0x74a872e8, 0x34db36df, 0x7493ba34,
  0x3508fa66, 0x747eef85, 0x3536b5be, 0x746a12df,
  0x356468e2, 0x74552446, 0x359213c9, 0x744023bc,
  0x35bfb66e, 0x742b1144, 0x35ed50c9, 0x7415ece2,
  0x361ae2d3, 0x7400b69a, 0x36486c86, 0x73eb6e6e,
  0x3675edd9, 0x73d61461, 0x36a366c6, 0x73c0a878,
  0x36d0d746, 0x73ab2ab4, 0x36fe3f52, 0x73959b1b,
  0x372b9ee3, 0x737ff9ae, 0x3758f5f2, 0x736a4671,
  0x37864477, 0x73548168, 0x37b38a6d, 0x733eaa96,
  0x37e0c7cc, 0x7328c1ff, 0x380dfc8d, 0x7312c7a5,
  0x383b28a9, 0x72fcbb8c, 0x38684c19, 0x72e69db7,
  0x389566d6, 0x72d06e2b, 0x38c278d9, 0x72ba2cea,
  0x38ef821c, 0x72a3d9f7, 0x391c8297, 0x728d7557,
  0x39497a43, 0x7276ff0d, 0x39766919, 0x7260771b,
  0x39a34f13, 0x7249dd86, 0x39d02c2a, 0x72333251,
  0x39fd0056, 0x721c7580, 0x3a29cb91, 0x7205a716,
  0x3a568dd4, 0x71eec716, 0x3a834717, 0x71d7d585,
  0x3aaff755, 0x71c0d265, 0x3adc9e86, 0x71a9bdba,
  0x3b093ca3, 0x71929789, 0x3b35d1a5, 0x717b5fd3,
  0x3b625d86, 0x7164169d, 0x3b8ee03e, 0x714cbbeb,
  0x3bbb59c7, 0x71354fc0, 0x3be7ca1a, 0x711dd220,
  0x3c143130, 0x7106430e, 0x3c408f03, 0x70eea28e,
  0x3c6ce38a, 0x70d6f0a4, 0x3c992ec0, 0x70bf2d53,
  0x3cc5709e, 0x70a7589f, 0x3cf1a91c, 0x708f728b,
  0x3d1dd835, 0x70777b1c, 0x3d49fde1, 0x705f7255,
  0x3d761a19, 0x70475839, 0x3da22cd7, 0x702f2ccd,
  0x3dce3614, 0x7016f014, 0x3dfa35c8, 0x6ffea212,
  0x3e262bee, 0x6fe642ca, 0x3e52187f, 0x6fcdd241,
  0x3e7dfb73, 0x6fb5507a, 0x3ea9d4c3, 0x6f9cbd79,
  0x3ed5a46b, 0x6f841942, 0x3f016a61, 0x6f6b63d8,
  0x3f2d26a0, 0x6f529d40, 0x3f58d921, 0x6f39c57d,
  0x3f8481dd, 0x6f20dc92, 0x3fb020ce, 0x6f07e285,
  0x3fdbb5ec, 0x6eeed758, 0x40074132, 0x6ed5bb10,
  0x4032c297, 0x6ebc8db0, 0x405e3a16, 0x6ea34f3d,
  0x4089a7a8, 0x6e89ffb9, 0x40b50b46, 0x6e709f2a,
  0x40e064ea, 0x6e572d93, 0x410bb48c, 0x6e3daaf8,
  0x4136fa27, 0x6e24175c, 0x416235b2, 0x6e0a72c5,
  0x418d6729, 0x6df0bd35, 0x41b88e84, 0x6dd6f6b1,
  0x41e3abbc, 0x6dbd1f3c, 0x420ebecb, 0x6da336dc,
  0x4239c7aa, 0x6d893d93, 0x4264c653, 0x6d6f3365,
  0x428fbabe, 0x6d551858, 0x42baa4e6, 0x6d3aec6e,
  0x42e584c3, 0x6d20afac, 0x43105a50, 0x6d066215,
  0x433b2585, 0x6cec03af, 0x4365e65b, 0x6cd1947c,
  0x43909ccd, 0x6cb71482, 0x43bb48d4, 0x6c9c83c3,
  0x43e5ea68, 0x6c81e245, 0x44108184, 0x6c67300b,
  0x443b0e21, 0x6c4c6d1a, 0x44659039, 0x6c319975,
  0x449007c4, 0x6c16b521, 0x44ba74bd, 0x6bfbc021,
  0x44e4d71c, 0x6be0ba7b, 0x450f2edb, 0x6bc5a431,
  0x45397bf4, 0x6baa7d49, 0x4563be60, 0x6b8f45c7,
  0x458df619, 0x6b73fdae, 0x45b82318, 0x6b58a503,
  0x45e24556, 0x6b3d3bcb, 0x460c5cce, 0x6b21c208,
  0x46366978, 0x6b0637c1, 0x46606b4e, 0x6aea9cf8,
  0x468a624a, 0x6acef1b2, 0x46b44e65, 0x6ab335f4,
  0x46de2f99, 0x6a9769c1, 0x470805df, 0x6a7b8d1e,
  0x4731d131, 0x6a5fa010, 0x475b9188, 0x6a43a29a,
  0x478546de, 0x6a2794c1, 0x47aef12c, 0x6a0b7689,
  0x47d8906d, 0x69ef47f6, 0x48022499, 0x69d3090e,
  0x482badab, 0x69b6b9d3, 0x48552b9b, 0x699a5a4c,
  0x487e9e64, 0x697dea7b, 0x48a805ff, 0x69616a65,
  0x48d16265, 0x6944da10, 0x48fab391, 0x6928397e,
  0x4923f97b, 0x690b88b5, 0x494d341e, 0x68eec7b9,
  0x49766373, 0x68d1f68f, 0x499f8774, 0x68b5153a,
  0x49c8a01b, 0x689823bf, 0x49f1ad61, 0x687b2224,
  0x4a1aaf3f, 0x685e106c, 0x4a43a5b0, 0x6840ee9b,
  0x4a6c90ad, 0x6823bcb7, 0x4a957030, 0x68067ac3,
  0x4abe4433, 0x67e928c5, 0x4ae70caf, 0x67cbc6c0,
  0x4b0fc99d, 0x67ae54ba, 0x4b387af9, 0x6790d2b6,
  0x4b6120bb, 0x677340ba, 0x4b89badd, 0x67559eca,
  0x4bb24958, 0x6737ecea, 0x4bdacc28, 0x671a2b20,
  0x4c034345, 0x66fc596f, 0x4c2baea9, 0x66de77dc,
  0x4c540e4e, 0x66c0866d, 0x4c7c622d, 0x66a28524,
  0x4ca4aa41, 0x66847408, 0x4ccce684, 0x6666531d,
  0x4cf516ee, 0x66482267, 0x4d1d3b7a, 0x6629e1ec,
  0x4d455422, 0x660b91af, 0x4d6d60df, 0x65ed31b5,
  0x4d9561ac, 0x65cec204, 0x4dbd5682, 0x65b0429f,
  0x4de53f5a, 0x6591b38c, 0x4e0d1c30, 0x657314cf,
  0x4e34ecfc, 0x6554666d, 0x4e5cb1b9, 0x6535a86b,
  0x4e846a60, 0x6516dacd, 0x4eac16eb, 0x64f7fd98,
  0x4ed3b755, 0x64d910d1, 0x4efb4b96, 0x64ba147d,
  0x4f22d3aa, 0x649b08a0, 0x4f4a4f89, 0x647bed3f,
  0x4f71bf2e, 0x645cc260, 0x4f992293, 0x643d8806,
  0x4fc079b1, 0x641e3e38, 0x4fe7c483, 0x63fee4f8,
  0x500f0302, 0x63df7c4d, 0x50363529, 0x63c0043b,
  0x505d5af1, 0x63a07cc7, 0x50847454, 0x6380e5f6,
  0x50ab814d, 0x63613fcd, 0x50d281d5, 0x63418a50,
  0x50f975e6, 0x6321c585, 0x51205d7b, 0x6301f171,
  0x5147388c, 0x62e20e17, 0x516e0715, 0x62c21b7e,
  0x5194c910, 0x62a219aa, 0x51bb7e75, 0x628208a1,
  0x51e22740, 0x6261e866, 0x5208c36a, 0x6241b8ff,
  0x522f52ee, 0x62217a72, 0x5255d5c5, 0x62012cc2,
  0x527c4bea, 0x61e0cff5, 0x52a2b556, 0x61c06410,
  0x52c91204, 0x619fe918, 0x52ef61ee, 0x617f5f12,
  0x5315a50e, 0x615ec603, 0x533bdb5d, 0x613e1df0,
  0x536204d7, 0x611d66de, 0x53882175, 0x60fca0d2,
  0x53ae3131, 0x60dbcbd1, 0x53d43406, 0x60bae7e1,
  0x53fa29ed, 0x6099f505, 0x542012e1, 0x6078f344,
  0x5445eedb, 0x6057e2a2, 0x546bbdd7, 0x6036c325,
  0x54917fce, 0x601594d1, 0x54b734ba, 0x5ff457ad,
  0x54dcdc96, 0x5fd30bbc, 0x5502775c, 0x5fb1b104,
  0x55280505, 0x5f90478a, 0x554d858d, 0x5f6ecf53,
  0x5572f8ed, 0x5f4d4865, 0x55985f20, 0x5f2bb2c5,
  0x55bdb81f, 0x5f0a0e77, 0x55e303e6, 0x5ee85b82,
  0x5608426e, 0x5ec699e9, 0x562d73b2, 0x5ea4c9b3,
  0x565297ab, 0x5e82eae5, 0x5677ae54, 0x5e60fd84,
  0x569cb7a8, 0x5e3f0194, 0x56c1b3a1, 0x5e1cf71c,
  0x56e6a239, 0x5dfade20, 0x570b8369, 0x5dd8b6a7,
  0x5730572e, 0x5db680b4, 0x57551d80, 0x5d943c4e,
  0x5779d65b, 0x5d71e979, 0x579e81b8, 0x5d4f883b,
  0x57c31f92, 0x5d2d189a, 0x57e7afe4, 0x5d0a9a9a,
  0x580c32a7, 0x5ce80e41, 0x5830a7d6, 0x5cc57394,
  0x58550f6c, 0x5ca2ca99, 0x58796962, 0x5c801354,
  0x589db5b3, 0x5c5d4dcc, 0x58c1f45b, 0x5c3a7a05,
  0x58e62552, 0x5c179806, 0x590a4893, 0x5bf4a7d2,
  0x592e5e19, 0x5bd1a971, 0x595265df, 0x5bae9ce7,
  0x59765fde, 0x5b8b8239, 0x599a4c12, 0x5b68596d,
  0x59be2a74, 0x5b452288, 0x59e1faff, 0x5b21dd90,
  0x5a05bdae, 0x5afe8a8b, 0x5a29727b, 0x5adb297d,
  0x5a4d1960, 0x5ab7ba6c, 0x5a70b258, 0x5a943d5e,
};

