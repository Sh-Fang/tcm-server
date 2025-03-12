# tcm-server
A RESTful API server of tcm

# API 文档

## 概述
本API提供了一个基于HTTP的接口服务，用于处理匹配请求和获取全局进度信息。服务通过`httplib`库实现，并支持POST和GET请求。

## 接口列表

### 1. 匹配请求接口
- **URL**: `/match`
- **方法**: POST
- **功能**: 接收匹配请求，解析输入参数，调用匹配算法，并返回匹配结果。

#### 请求参数
- **Content-Type**: `application/json`
- **Body**:

  ```json
  {
    "stream_path": "./stream.txt",
    "query_path": "./query.txt"
    // 其他参数
  }
  ```

#### 响应
- **状态码**:
    - `200`: 请求成功，返回匹配结果。
    - `400`: 请求无效，返回错误信息。

#### 示例
- **请求**:
  ```bash
  curl -X POST http://localhost:8081/match -H "Content-Type: application/json" -d '{"param1": "value1", "param2": "value2"}'
  ```
- **响应**:
```json
{
  "statistical_info": {
      "runtime": "123ms",
      "stream_file": "stream.txt",
      "query_file": "query.json",
      "dataset": "sample_data",
      "query_type": "subgraph_match",
      "match_count": "10"
  },
  "all_query": {
      "all_query": [
          {
              "q_id": "q1",
              "src_id": "node1",
              "tar_id": "node2",
              "e_lab": "edge1",
              "src_lab": "A",
              "tar_lab": "B"
          }
      ]
  },
  "all_match_result": {
      "all_match_result": [
          [
              {
                  "src_id": "node1",
                  "tar_id": "node2",
                  "e_lab": "edge1",
                  "src_lab": "A",
                  "tar_lab": "B",
                  "timestamp": "2025-03-12 10:00:00"
              }
          ]
      ]
  }
}
```

### 2. 获取进度接口
- **URL**: `/progress`
- **方法**: GET
- **功能**: 返回全局进度和状态信息。

#### 请求参数
- 无

#### 响应
- **状态码**: `200`
- **Content-Type**: `application/json`
- **Body**:
  ```json
  {
    "global_progress": "进度百分比",
    "global_status": "当前状态"
  }
  ```

#### 示例
- **请求**:
  ```bash
  curl http://localhost:8081/progress
  ```
- **响应**:
  ```json
  {
    "global_progress": "50",
    "global_status": "Processing"
  }
  ```

## 日志记录
- 服务会记录每次请求的详细信息，包括请求时间、客户端IP、请求方法、路径、状态码和响应体。
- 日志会实时输出到控制台。

## 服务启动
- 服务运行在`http://localhost:8081`。
- 使用`startServer()`函数启动服务。

## 注意事项
1. 请求体必须符合JSON格式，否则会返回`400`错误。
2. 进度接口返回的进度值为字符串类型，表示当前进度的百分比。
3. 服务仅支持`POST`和`GET`方法，其他方法会返回`405 Method Not Allowed`。

## 版本信息
- **API版本**: 1.0
- **最后更新**: 2025年03月12日

你可以开发的功能主要取决于你的应用场景，比如是用于学术研究、企业应用还是开源工具。以下是一些功能建议，按照不同层面划分：

# 1. 数据管理与预处理

   - 图数据导入/导出：支持从 CSV、JSON、GraphML、GML、Neo4j、NetworkX 等格式导入和导出图数据。
   - 数据清洗：去除孤立节点、重复边、异常数据点等，提高匹配质量。
   - 索引构建：基于边中心索引、k 部图索引等优化查询效率。
   - 可视化编辑：提供 GUI 界面，让用户手动编辑图数据。
# 2. 子图匹配核心功能
   - 精确匹配：支持同构匹配、同构子图查询。
   - 模糊匹配：支持带噪声的子图匹配（例如允许部分节点或边的差异）。
   - 结构化查询：支持用户定义子图查询模式，例如 Cypher 查询语句或基于 DSL（领域特定语言）的查询语法。
   - 模式挖掘：自动发现常见子图模式，提高匹配效率。
   - 增量匹配：当主图动态变化时（增删节点或边），提供高效的增量更新机制。
# 3. 系统优化
   - 索引加速：利用索引技术加快匹配速度，如 k 部图索引、哈希索引等。
   - 并行计算：利用多线程或 GPU 计算加速大规模子图匹配。
   - 分布式计算：支持 Spark GraphX、DGL（Deep Graph Library）等，实现大规模图匹配。
# 4. 交互与可视化
   - 交互式查询：用户可以输入子图模式，系统实时返回匹配结果。
   - 可视化匹配结果：以图的形式展示匹配结果，例如高亮匹配的子图部分。
   - 日志与统计分析：记录匹配过程，提供性能分析、匹配成功率等数据。
   - 查询优化建议：基于查询历史和索引信息，给用户推荐更高效的查询方式。
# 5. API与集成
   - RESTful API / GraphQL API：提供标准 API，支持外部系统调用。
   - 数据库集成：支持与 Neo4j、PostgreSQL（pgGraph）、ArangoDB 等图数据库交互。
   - AI 结合：结合图神经网络（GNN），提高子图匹配的准确性。
# 6. 其他扩展功能
   - 时间序列匹配：如果你的数据涉及时序约束（timing order），可以考虑引入动态子图匹配。
   - 模式演化分析：分析子图随时间变化的趋势，适用于社交网络、网络安全等领域。
   - 多层次匹配：支持从不同抽象层次匹配子图，例如在属性图、知识图谱中匹配不同层级的模式。 
# 下一步建议
   如果你是一个人开发，建议优先实现 **数据导入+索引+核心匹配+可视化**，这样可以尽快形成一个可用的原型。后续再考虑性能优化、分布式扩展和 AI 结合。