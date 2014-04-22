AdaptiveGraphcuts
========

### 动机

为了验证`MultiLayerGraph`在分割时具有良好的边界约束性，写的一个测试Demo

### 目的

根据用户给定输入类别数，测试分别用`Kmeans`和`MultiLayerGraph`分割得到的不同结果，一方面测试MLG的优越性；另一方面提供一个可实践的MLG`demo`

### 效果
原图
![moondark](moondark.jpg)

输入等于3时，用Kmeans分割

![Kmeans](SegmentByKmeans.png)

用`MultiLayerGraph`分割：

![MultiLayerGraph](SegmentByMultiLayerGraph.png)


