# SearchEngines

### 简介
本项目实现一个非常基础的搜索引擎，核心部分是“布隆过滤器”和“分词器”，分别用c++和python两种语言实现


## [布隆过滤器](https://en.wikipedia.org/wiki/Bloom_filter)

```
布隆过滤器是大数据领域的一个常见算法，它的目的是过滤掉那些不是目标的元素。也就是说如果一个要搜索的词并不存在与我的数据中，那么它可以以很快的速度返回目标不存在。
```

## 分词

```js
分词的目的是要把我们的文本数据分割成可搜索的最小单元，分词对搜索结果影响很大，如果没有将搜索的关键词分出来是无法搜出结果的。
```

## 具体实现

```js
添加文本过程：将文本放入容器得到索引，然后对文本进行分词将所有分词结果逐个放入映射表，并且加入到布隆过滤器中。
搜索文本过程：先用布隆过滤器检查文本是否存在，然后检查映射表,如果找到就通过索引结果集找到对应的数据返回。
在搜索过程中，用And和Or来实现更复杂的搜索逻辑只需要对结果集进行补集或者差集操作即可

```