# Enternity
My GameEngine Based on OpenGL

Blending:red is under the blue 
	ps shder(blue) ----> framebuffer(red)
	source: ps shder output
	destination: framebuffer

Batch Rendering

Ref的目的：为了不复制资源，我们用const T&，但是在多线程渲染或者其他场景下，在堆上创建的资源可能已经被释放了，所以使用Ref:addRef, Ref:release


Entity Component System(ECS 实体对象系统):Data drived
Scene---->GameObjects------>Components
场景需要能够存储实体
Entity:实体  Component:组件（数据） System: 方法/功能


mesh.bin

header:
	unsigned int VertexCount(顶点类型 默认写死，float3:position, float3:normal, float2:texcoord)
	unsigned int IndexCount(索引类型 默认写死，unsigned int)


模板缓冲:
	1、启用模板缓冲的写入。
	2、渲染物体，更新模板缓冲的内容。
	3、禁用模板缓冲的写入。
	4、渲染（其它）物体，这次根据模板缓冲的内容丢弃特定的片段。
	

Box2d: 
	1、world 
	2、rigidBody:刚体（静态刚体， 动态刚体）
	3、collider：对撞机

Assimp: 加载模型 aiScene, aiMesh, aiMaterial

骨骼动画:
	1、骨骼空间与模型空间
	aiBone->mOffsetMatrix : 从模型空间变换到骨骼空间的变换矩阵
	aiNode->mTransformation : 从自己的骨骼空间变换到父亲节点的骨骼空间

	Model Space * mOffsetMatrix ---> Bone Space * mTransformation ---> Parent Bone Space --->...............


glm 矩阵乘法得反过来写
https://www.cnblogs.com/makejeffer/p/7652771.html

TODO: 1、粒子系统，地形系统（曲面细分，LOD）
	  2、代码重构


1。输入管理模块，用来获取用户输入

2。策略模块，用来执行策略

3。场景管理模块，用来管理场景和更新场景

4。渲染模块，用来执行渲染和画面输出

5。音频音效模块，用来管理声音，混音和播放

6。网络通信模块，用来管理网络通信

7。文件I/O模块，用来管理资源的加载和参数的保存回复

8。内存管理模块，用来调度管理内存上的资源

9。驱动模块，用来根据时间，事件等驱动其它模块

10。辅助模块，用来执行调试，log输出等辅助功能

11。应用程序模块，用来抽象处理配置文件，特定平台的通知，创建窗口等需要与特定平台对接的部分


场景的剖分与管理:通过将场景分割为场景物体，将场景物体分割为组件，将组件进行标准化归纳统一。

文件读取：1、一般二进制文件(自己知道二进制的内容,shader文件)
		  2、模型文件（obj、fbx ......），由assimp加载
		  3、贴图文件，由stb_image加载


场景：scene负责维护自己的实体(uuid : entity)
      scenemanager负责维护所有创建的scene(uuid : scene)

RenderSystem: 接受drawcall命令放在队列中， 在tick的时候从队列中取出drawcall命令执行

!!!!写多线程一定注意变量的生命周期:
	例如void BlobLoader::loadTextureImpl(Blob*& blob, const std::string& filePath, int desired_channels /*= 0*/)
	int desired_channels 为局部变量, 直接使用可能导致问题（形参可能被释放）