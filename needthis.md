# Dấu hiệu nhận biết các dạng bài toán trong lập trình

## Dạng bài yêu cầu gộp các điểm | vị trí bằng các thao tác hoặc khi thực hiện thao tác các điểm bị trùng và cần biết vị trí, thao tác có thể yêu cầu truy vấn vị trí của các điểm nằm trong tập hợp nào hoặc in ra thứ tự/ kích thước của thành phần :
- Sử dụng **DSU** để gộp các thành phần trên trong O(4)  : path compression và union by rank/size

## Dạng bài value contribution :
- Thường dùng trong các bài bắt phải duyệt N^2 nếu vét cạn bằng cách check nhiều lần. và mỗi giá trị có thể xuất hiện nhiều lần 
	- value contribution là chìa khóa
 - tính xem phần tử a_i là đóng góp vào mảng/cây bao nhiêu lần/ tính vùng ảnh hưởng
	 - nếu là mảng : **Monotonic stack** : **( áp dụng cho tính chất bắc cầu, tham lam cục bộ loại bỏ giải pháp không ảnh hưởng tới tương lai )**
	 - nếu là cây : **DSU**
## Dạng bài range query :
- Nếu truy vấn tổng -> **prefix sum.* :
	- nếu N  <= 1e3 thì có thể nghĩ tới **prefix sum 2d**.
	- Đặc điểm của **prefix sum 2d** : 
		- **truy vấn  tính tổng mọi cặp chỉ số (i, j) thuộc (L, R) op(a_i, a_j) -> lưu pref(i, j) = op(a_i, a_j). op(a_i, a_j) là thực hiện phép tính của a_i, a_j**
		- **truy vấn có 2 điều kiện : (L1, R1) và (L2, R2) : tần số hoặc là range query**
- Nếu không phải tính tổng, truy vấn có update -> **Segment tree/Sqrt decomposition/Mo algorithms**

## Dạng bài cây :
- khi có N đỉnh và N - 1 cạnh
- nếu bài toán cần truy vấn đường đi (u, v) -> dùng **lca + binary lifting** + **sparse table** nếu có thêm những điều kiện khác
-  N <= 1e3 -> duyệt brute force lưu vào mảng 2 chiều
-  truy vấn subtree của u : **Segment tree/Mo trên cây**

## Dạng bài tham lam
- Thấy được nếu luôn chọn tối ưu cục bộ thì có thể đạt được tối ưu toàn cục thì sẽ là tham lam
- liên quan đến sort, monotonic stack

## Dạng bài Tìm kiếm nhị phân
- Tìm nhị phân trên kết quả
	- nhìn thấy đáp án có tính chất đơn điệu
	- gọi f(x) là giá trị tối ưu. thì với mọi y > f(x) -> không thỏa, y <= f(x) -> thỏa mãn, và ngược lại
- Tìm kiếm trong mảng :
	- tối ưu bài toán từ N ->  log N nếu bài toán thỏa mãn tính chất đơn điệu

## Dạng bài Quy hoạch động
- giải được bằng đệ quy
- có thể define state
- có base case
- cố gắng transition và nghĩ xem cần bao nhiêu trạng thái để có thể chuyển dễ dàng
- tìm kết quả của bài toán trong mảng **DP**
- tối ưu hóa Quy hoạch động từ N^2  -> N log N hoặc N
	- sử dụng TKNP, Segment tree, Sorting -> Log N
	- sử dụng prefix sum, monotonic queue -> O(1)

## Dạng bài đồ thị
- Tìm mạng lưới liên thông sao cho tổng chi phí nhỏ nhất : **Cây Khung Kruskal**
- Đường đi ngắn nhất :
	- trọng số âm : 
		- **SPFA** (N <= 1e3)
		- **Floyd** (N <= 1e2)
	- trọng số dương : 
		- **Djikstra**
	- APSP : 
		- đồ thị thưa ->  **Dijkstra** (N <= 1e3),
		- đồ thị đặc -> **Floyd** (N <= 1e2)
	- đồ thị có hướng không chu trình : 
		- **Topo Sort**
	- Đa nguồn : 
		- **Dijkstra/BFS**
	- Trọng số 0/1 hoặc 1 :
		- **BFS**
- Đồ thị có hướng không chu trình :
	- khi biểu diễn mối quan hệ 1 chiều, không có mối quan hệ tam giác....
	- **Topo sort + DP**
- Chu trình : 
	- Đồ thị Vô hướng : **DSU**
	- Đồ thị Có hướng : **DFS stacktrace**
	- Chu trình âm : SPFA ( nếu 1 đỉnh được relax V-1 lần  ), Floyd ( dist(i, i) < 0 )
- Khớp/Cầu/SCC/BCCS/ECC:
	- Đồ thị vô hướng:
		- Khớp : 
			- **Các điểm quan trọng/chiến lược trong đồ thị, các đỉnh nếu loại bỏ thì không còn liên thông**
			- Có truy vấn (u, v) liên quan tới khớp 
				- sử dụng **Block cut tree**
	    - Cầu :
			 - **Các đường đi quan trọng/chiến lược trong đồ thị, đường đi nếu bị loại bỏ sẽ không còn liên thông**
			 - nếu đề yêu cầu liên quan đến các cầu ( cần tự suy luận ) 
				 - sử dụng **Bridge Edge tree**
	- Đồ thị có hướng:
		- SCC tìm low link và các SCCs
		- Nếu bài toán cần xử lí trên DAG nhưng đề lại cho SCC -> tạo **Condensation graph**
