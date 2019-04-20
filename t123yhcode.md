# t123yh’s Decode

>密码学是关于如何在敌人存在的环境中通信。——罗纳德·李维斯特, 密码学者

## 题目描述

>有的题目，它看起来很长，但写起来不超过 100 行。比如银行排队；比如这道题目。——t123yh

*t123yh* 是一名程序员，最近他写了一个聊天软件 *HubChat* 。在选择消息对消息加密方法的过程中，*t123yh* 想到了一种混合的密码算法。

在 *t123yh* 的加密算法中，我们使用如下方法构造密码：

<span style="color:red;font-size:30px">题目真的不难，看不下去的注意参考提示。</span>

对于密钥 $K=k_1k_2k_3...k_m$ ，当明文 $O=o_1o_2o_3...o_n$ 时，得到密文 $E=e_1e_2e_3...e_n$，其中 $e_j=f(o_j, k_j)$

映射 $z=f(x,y)$ 的规则如下：

![函数f](https://i.loli.net/2019/04/19/5cb9919d5745b.png)  

注意：  
1.这个映射**保持明文和密文字母的大小写**，简单来说：

* 当 $o_j​$ 是大写时，$e_j​$ 也是大写；  
* 当 $o_j​$ 是小写时， $e_j​$ 也是小写；  

*这要求你在进行加密时判断被加密的字符大小写*  
2.当明文 $I​$ 的长度大于密钥 $key​$ 的长度时，将密钥 $key​$ **重复使用**。为了确保安全性，每次用完一遍密钥之后，密钥就会发生改变，将每一位后移，并将最后一位放在第一个的位置。  
举例来说，"abcd" 这个密钥被使用一轮之后（这里的一轮定义为 $f(O_i,K_i)$ 中的 $K_i$ 分别取过'a','b','c','d'），就会变成 "dabc" ，进行下一轮的加密。

*t123yh* 叉了会腰之后，突然觉得这个算法应该更牛逼一点，比如通过同一个过程就可以完成加密和解密，于是他又构造了一个被称作“反射器”的机制。  
如果用函数 $g(x)$ 来表示反射器，那么它将有如下性质：若 $g(m)=n$ ，则有$g(n)=m$，并且保证 $m \not = n$。  

*t123yh* 决定随机生成一个 $g(x)$ ，其形式为

```c
char g[27];

char g(char x)
{
    return g[x-'a'];
}  
```

其中，`char g[27]` 是由标准输入给出的一串长度为 26 的字符串，其每个字符分别对应 'a', 'b', ..., 'z'

于是我们可以进一步构造这样一种加密规则：

1.*将明文通过原来的算法“加密”*  
2.*然后将获得的字符输入反射器*  
3.*再将反射器输出的字符用同一位密钥“解密”，得到最终的密文。*  

显然，如果使用同样的密钥，用相同的顺序操作密文也可以获得其明文。

用公式表示则是：  
$E_i=f^{-1}(g(f(O_i,K_i)),K_i)$  
其中

* $E_i$ ：密文第 $i$ 个字符  
* $O_i$ ：明文第 $i$ 个字符  
* $K_i$ ：密钥第 $i$ 个字符  
* $f$：上面的图对应的加密函数  
* $f^{-1}$：$f$的反函数（需要你们自己来推，这个难度不大）  
* $g$：反射器

由于网络问题，待解密的密文串并不是按照时间顺序排列的，但是，好在 *t123yh* 在每条消息的前面加上了格式为 *YYYY-MM-DD-HH-MM-SS* 的时间戳。你可以借助这个时间戳在解密之后对明文进行排序，并按照时间顺序输出。

## 输入输出格式

### 输入格式

多行输入数据。

第一行：一个数字 $n$ ，代表接下来有 $n$ 条被加密的信息。

第二行：一个字符串，表示密钥 $key$，长度不超过 **100**，其中**仅包含大小写字母**。

第三行：一个字符串，表示 $g(x)$ 加密用到的 `char g[27]` 。

第四行起的 $n$ 行：消息字符串，其包括形如 *YYYY-MM-DD-HH-MM-SS* 和一串表示经加密后的 **密文$O$** 字符串，每行长度不超过 **1000** 字符，其中 **密文仅包含大小写字母** ，二者中间以空格分隔。

### 输出格式

$n$ 行字符串，按照时间顺序输出**时间戳**和**字符串**表示输入密钥和密文所对应的明文，每行中间以一个空格分隔。

## 样例数据

### 样例输入

```plain
4
CompleteVictory
nukptihgfzcqxawdlvyebromsj
2019-04-20-20-10-00 XkayyJnnmi
2019-04-19-05-13-59 pjsVM
2019-04-20-20-15-26 DuzpiVjulmlu
2019-04-18-15-30-44 xdsznmumpvxu
```

### 样例输出

```plain
2019-04-18-15-30-44 hhhhhhhhhhhh
2019-04-19-05-13-59 tyhNB
2019-04-20-20-10-00 HelloWorld
2019-04-20-20-15-26 GreetFromtyh
```

### 样例解释

**前缀的>>>表示输入**

```plain
>>> nukptihgfzcqxawdlvyebromsj
get Reflector:nukptihgfzcqxawdlvyebromsj
DEBUG Message:
Key:completevictory,
//  ^这个地方^注意，我们在解密之前将密钥转换成了全部小写

Origin:
>>> XkayyJnnmi
DEBUG Message: Key:completevictory, Origin:XkayyJnnmi
f: x -> z       f1: j -> h
f: k -> y       f1: s -> e
f: a -> m       f1: x -> l
f: y -> n       f1: a -> l
f: y -> j       f1: z -> o
f: j -> n       f1: a -> w
f: n -> g       f1: h -> o
f: n -> r       f1: v -> r
f: m -> h       f1: g -> l
f: i -> q       f1: l -> d
HelloWorld

>>> pjsVM
DEBUG Message: Key:completevictory, Origin:pjsVM
f: p -> r       f1: v -> t
f: j -> x       f1: m -> y
f: s -> e       f1: t -> h
f: v -> k       f1: c -> n
f: m -> x       f1: m -> b
tyhNB

>>> DuzpiVjulmlu
DEBUG Message: Key:completevictory, Origin:DuzpiVjulmlu
f: d -> f       f1: i -> g
f: u -> i       f1: f -> r
f: z -> l       f1: q -> e
f: p -> e       f1: t -> e
f: i -> t       f1: e -> t
f: v -> z       f1: j -> f
f: j -> c       f1: k -> r
f: u -> y       f1: s -> o
f: l -> g       f1: h -> m
f: m -> u       f1: b -> t
f: l -> n       f1: a -> y
f: u -> n       f1: a -> h
GreetFromtyh

>>> xdsznmumpvxu
DEBUG Message: Key:completevictory, Origin:xdsznmumpvxu
f: x -> z       f1: j -> h
f: d -> r       f1: v -> h
f: s -> e       f1: t -> h
f: z -> o       f1: w -> h
f: n -> y       f1: s -> h
f: m -> q       f1: l -> h
f: u -> n       f1: a -> h
f: m -> q       f1: l -> h
f: p -> k       f1: c -> h
f: v -> d       f1: p -> h
f: x -> z       f1: j -> h
f: u -> n       f1: a -> h
hhhhhhhhhhhh

//之后可以使用快排对时间进行排序，然后输出答案即可。
```

## 数据范围与提示

注意原文的大小写和数组下标。
$ 100<n<1000 $  
**密钥 $key$**，长度不超过 **100**，其中**仅包含大小写字母**。  
**密文$O$** 字符串，每行长度不超过 **1000** 字符，其中 **密文仅包含大小写字母** ，二者中间以空格分隔。

**处理过程中请将 $key$ 转小写！！！**  
**处理过程中请将 $key$ 转小写！！！**  
**处理过程中请将 $key$ 转小写！！！**

**可以使用快排对时间进行排序，然后输出答案即可。**  
**核心步骤：**  

```c
message[Cnt].E[i] = f1(g(f(message[Cnt].O[i], key[i % len])), key[i % len]);
```

其中 `f1` 表示 `f` 的逆函数，`g` 是反射器，取 `key[i%len]` 保证密钥重复使用的过程中不会越界。

**注意事项**  
<span style="color:red;font-size:30px">1.在每次解密开始前要还原密钥。</span>  
<span style="color:red;font-size:30px">2.注意判断是否需要在加密前转动密钥。</span>
