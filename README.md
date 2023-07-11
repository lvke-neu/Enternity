0.004
1、资源管理（资源加载线程）

AssetID, Asset, AssetLoader


2、点选framebuffer, 天空盒， 后处理（场景纹理渲染到一个quad上）, 阴影

3、粒子(https://blog.csdn.net/cooclc/article/details/120669799)，地形...

4、视锥体裁剪

(重新basic primitive mesh----->framebuffer 多个color texture----->重新实现渲染到quad-------->混合渲染:先绘制所有不透明的物体,对所有透明的物体排序,按顺序绘制所有透明的物体)------>简单粒子实现

用hdr填充cubemap


blobloader:"shader://", "texture://", "mesh://"
