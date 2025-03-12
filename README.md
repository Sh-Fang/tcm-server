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


## 服务启动
- 服务运行在`http://localhost:8081`。

