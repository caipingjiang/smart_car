# 你好， 世界！😄
## 十九届智能视觉备战
### 2024/4/10
昨晚偶然间又看了木哥的备战“日记”， 感受很多，颇受启发。感受到有许多值得咱们学习的地方：
- 每个一段时间就反思总结， 回顾近段时间做了什么，明晰下一阶段应该做什么
- 提高效率，有时不要太意气用事，多点理性
- 学习永无止境，热爱就是动力，学习英语即使如此，不必感到烦恼，把它权当你技术学习上的工具，每天坚持
  当然还有许多值得学习借鉴的地方，哈哈，就这么简单写点吧，以后这可以作为我们交流、分享讨论的地方，鼓励大家也来多写写心得体会，bye

### 2024/4/11
目前阶段现状：
1. PCB焊接未搞定(如果板子没问题，尽量在下周结束之前完成-21号)
2. 卡片数据集还有许多类别未拍，可以每天有空就拍一类，轮流拍，完成每日任务任务，不要过于依赖学弟， 导致拍的效率很低？（江老师说得对，压榨学弟不如压榨自己）
3. 车硬件总体调试（尽快要完成了，不能再拖， 周末之前完成）
4. 元素识别稳定性加强，以及在元素部分赛道的运动控制还没完成
5. OpenArt 目标检测以及串口传输数据（如何确保信息的准确性，考虑滤掉一些信息）

故下周主要任务就是4，5，争取让车车先跑起来，模型的准确性先不提
这周拍完数据集，打完标签开始炼丹，不能再拖了


### 2024/4/11
今日工作，像机器人一样拍照，莫得感情，明天继续，拍完四类，难受。
### 2024/4/14
受到木哥指点，认真检查驱动板的焊接，发现普遍存在的虚焊问题，焊了一天板子成功修好以前失败的三块驱动板，焊接技术进阶
数据集拍完，驱动板完成。

### 2024/4/16
下阶段任务 完成二代机械结构，框架加宽，机械臂优化，这次依然使用3d打印，后期优化替换
           探索炼丹技巧
           定下目标检测及分类识别的思路，测试openart可以运行两个模型，但可能是框选不标准导致识别率极低。目标检测重拍，如何拍？
           争取下周之前焊好主板，将车车以前学长的硬件结构替换为自己的，完成硬件任务
           最最最最重要！！！！！！背单词，考四级！

### 2024/5/1
   五一九天假？直接完赛？
   目前阶段现状：主板焊完测试完成，硬件结构以全部替换，机械结构完成，硬件任务完成
                炼丹一直是废丹，继续探索炼丹技巧
                控制代码不断完善，十字运行状态良好，下一步与openart结合进行控制，捡卡片的思路？
                openart分类识别时如何准确的框选出图片？
                调参这种事现阶段还是不要浪费太多时间，还没到死磕的时候目前就是调差不多能用就行吧
       九天的假期相比于之前零碎时间效率还是很高的，这段时间争取完成大部分任务，这段时间也是通宵了两天，（江老师是真的狠人，
     动不动就要调一晚上，相比江老师做的任务量，非常的自愧不如，比起江老师感觉自己有点摆，无比惭愧。注：后面打的都是身体战，如果现在不好好休息，
     后面是绝对撑不住的，江老师保重身体啊！）希望可以利用这次假期完赛吧。（献祭一个江老师）


### 2024/5/2

### 2024/5/3
现在是早上五点，差不多熬了一晚上，现在倒是挺精神的😂，张老师说的没错：后面打的都是身体战！回过头来看看这两三天的调车时光，确实，这就是差距的，一个代码写出来总会遇到各种bug,总是要调试很多次取找出bug所在，每次烧录完程序自信满满地以为这次绝对能行，可最后往往以打脸结束。代码框架先在脑海中初具雏形，到反复调试，找bug, 能运行，考量优化，其实我觉得有很大一部分时间浪费在找bug上。有时觉得自己效率太低，调了半天车，没什么进展，往往内耗自己的情绪；有时做一个事情，半路里觉得“有必要”去先完成另外一件事情，另一件事情做了回儿，觉得另另一件事应该先完成，哈哈，这就是顾此失彼啊，没有把握重点。每天先明晰第一优先级要做的是什么，如果被其他打断，有必要去做那么不是很有必要的事吗？往往是做这做那，就忘了根本的目的。希望以后引以为戒

前段时间张老师也是花了很多时间完成了驱动板和主板的焊接，也算是取得了突破性进展，我要称之为“大交汉武帝”，这几天调车哥们也是一起肝啊，也是辛苦了张老师咧
五一假期已过半，还有几天时光，分析一下下一阶段的工作：
- 练得一手好单，张老师也是练了很多丹了，但效果不是那么令人满意，下一阶段和张老师探讨一下，请教学长
- 该上openart了，先挑卡片矫正，目标检测若效果还行可以加上目标检测看看矫正效果
- 组织一下几个摄像头与核心板的通讯，分析一下总体通讯（小车控制）逻辑
- 数字字母的分类数据集应该也可以拍一拍了，这个效果应该很好
- 可以先拿个MCX Vision玩玩，了解以下怎么使用？


### 2024/5/6
 ！！！！丹成！！！！！
 也是和兄弟们又通宵一天，这次也是有两个学弟的陪伴，学弟的效率也是很高的，一晚上就打完了几千张照片的标签，不知道这算不算压迫学弟😝。
 也是在今天早上终于成神丹，过程也是有点难崩，我可能已经错过了好几次成神丹的机会了，前面无数次效果令人不满意的废丹其实是因为验证错误的问题，
 他们很有可能是神丹的😭，具体原因是逐飞给的分类识别的脚本 img.copy(r.rect()) 的使用错误，它并没有copy出感兴趣区域，而是使用的整个图像，
 这也是在使用目标检测后框出不理想框反而判断更精准而发现，因而出现了种种我们认为不理想的丹，将它改为 img1 = img.copy(1,1, r.rect())  
 就可以了，从中的感悟也是颇深😊。
  放假的这段时间虽然没有完赛但效率也是非常高的，也是和江老师通宵了四五天，现在生物钟都混乱了

- 完成炼丹任务
- 目标检测训练完成，90度分类目标检测良好，虽然可能框的不太准确，但好在丹硬，识别率还是非常高的，130度目标检测效果不太好，会出现近处标不出的问题，后面可能需要重练
- 数字字母的分类识别虽然只练了150多轮，准确率也是高的离谱
- 今天还发现调整openart的亮度也就是曝光时间会影响帧率，在降低曝光时间后帧率提高显著，所以补光灯变成了非常有必要了
- 目前来说任务就只剩和openart结合进行控制了，至于其他的暂且把他们归为优化项（换五分类？换碳板？），目前保证先完赛吧
- 自从调车后也是有点厌学，四级已经一个月没看了😭😭😭，感觉需要找点时间学学四级😔😔

### 2024/5/22
近两周进度推进缓慢，有些停滞
目前mcx已能用于目标检测，部署到实际的行车环境，今晚简单调了下，还有些小问题。
- 弯道可能识别不到卡片，可能是参考点的选择不太合理或者距离计算公式得优化
- 有时会误识别，导致转错方向，why?
- 仓舵机仍是一大问题，时不时还会发癫痫，今晚换了线，明天再试试会不会有问题
- bug:有时转向后会倒着走？
- 主板电源电路的问题，现在先放放？？？？？

下一阶段（6/1之前）：
- 把上面提到的问题，解决
- 把分类加上去，实现与仓配合
- 十字环岛逻辑控制完成
- 放置卡片

加油啊xdm，完成上面的内容也基本完赛了，**提高效率与执行力，不要再拖了**
<u>时间过得很快!!!</u>
<u>时间过得很快!!!</u>
<u>时间过得很快!!!</u>
早日完赛！⛽

### 2024/6/5
从前几天开始已经陆续完赛了，昨天又熬了一夜，解决了很多的bug,对控制进行了优化，运行起来丝滑了许多，目前识别和分类的正确率也得到保证了，到目前为止可以说已经基本完赛，若不提完赛用时的话运行起来还算比较稳定，有一定鲁棒性。虽然比预期的完赛日期晚了几天，但也总算完赛了，先庆祝一下🥳🎉

回归之前的问题，这里简单做下总结：
1.卡片的距离计算公式似乎不用太精确，以前以为mcx的前瞻因该很远，故需判断卡片的距离，但目前我们的mcx的前瞻调的较低，画面中只要有卡片，说明就已经不远了，所以这里简单的用像素点之间的距离来代表两者之间的距离，效果也是可以的，所以啊空想不如实际去动手试一下
2.仓舵机的问题之前一直萦绕了我们很久，也换过舵机，买过新舵机，仍然不行，最后发现是**杜邦线接口松动**的问题，只能说"踏破铁鞋无觅处，得来全不费工夫"，现在仓转的很标准，回想之前的转角，一会就差个5度10度，不然就疯狂抖动，现在心情舒畅了
3.转向后倒着走因为识别到了车底盘，同时之前的位置矫正如果坐标不刷新就会一直保持上一状态，导致可能走出赛道，现已改进

下一阶段就是不断测试，不断找潜在的bug,同时进行优化，提高稳定性与完赛速度，目前有以下几点：
0.首先把剩下的坡道和障碍物解决
1.用于分类的目标检测框照片可能还是稍有问题：可以考虑重新框，框得越准自然分类的正确率就会越高
2.加上错误修复，**提高整体的容错性**，比如即使在十字逻辑发生了错乱也不影响在环岛进行操作
3.之前的边界矫正稍微还有点问题，看看能优化进一步提高鲁棒性
4.去掉不必要的延时，在保证卡片识别正确率的基础上加快运行速度，看看能不能到**5min**以内
5.考虑在mcx端对目标直接进行过滤操作，因为有一定概率会误识别停下来，虽然不影响后面的执行，但挺费时间
6.代码优化：尽量把之前的参数声明在全局变量，把相同逻辑封装起来只需改变全局参数即可调参，而不用在相应代码段一个一个一次该让参数好改，易改，一目了然
7.结构优化：补光灯可以加上，仓换新版，框架的强度可以提升，前面支撑摄像头的碳杆得想办法限位，这个最好让他没有活动空间

**说长也长，说短也短，7月份就开始比赛了，6月又有不少考试，一个月过得是真的快，所以啊，后面不能松懈，提高执行力**

