# CEDumpPlugin
CE Dump 内存读写

# 编译
#### 本项目编译环境使用 Clion + cmake + vs2022, 在 Clion 的 cmake 配置中选择vs2022编译工具链进行编译

# 使用
### 跳转到 CEPlugin_InitializePlugin 方法的  memTools.init(R"(test\)") 代码把test路径换成自己dump文件夹路径的上级路径
`memTools.init("Dump目录的上级目录");`
### 编译完成后打开CE 7.5 ，在设置选择CEDumpPlugin.dll插件即可

# 如何Dump内存
#### 使用下面的MemTools仓库代码进行Dump

# 关于
* [CheatEngine-DMA(CE DMA内存插件)](https://github.com/Metick/CheatEngine-DMA)
* [MemTools(内存读写、dump工具)](https://github.com/bbgsm/MemTools)