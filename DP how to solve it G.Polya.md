
## 1. Understand the problem - hiểu vấn đề


### _What is the unknown? What are the data? What are the conditions?_

Trong DP, điều này tương đương:

- **Unknown** → giá trị cần tối ưu (max / min / count / exist)
- **Data** → input + constraints + đề bài
	- Có thể phát biểu lại đề bài để dễ hiểu hơn không
	- Có thể dự đoán độ phức tạp từ dữ liệu không 
- **Conditions** → ràng buộc ảnh hưởng đến quyết định
	- Hãy viết lại các điều kiện thành 1 danh sách
	- Phát biểu lại các điều kiện theo toán học
## 2. Devising a plan - lập kế hoạch

### _Liên hệ giữa dữ liệu và ấn số_ 

- Biến đổi dữ liệu đã có thành 1 hướng xác định để dễ tiếp cận
	- sort, map, compress, prefix, suffix, block, subsequence, tree....
- Tìm các tính chất đặc biệt của bài toán sau khi đã phát biểu lại đề bài
	- brute force
	- Dựa vào các định lý, dạng bài đã gặp
- Có thể chia nhỏ bài toán thành bài toán con không
	- Nếu ta giải được các bài toán con a, b, c,... Liệu các bài toán đó có đóng góp vào bài toán lớn hơn là A chứa các bài toán con a, b, c...
	- Nếu ta cố định 1 phần rằng buộc/dữ liệu/yêu cầu thì có thể tách bài toán thành các bài toán con không.
	- Tạo mối liên kết giữa rằng buộc, yêu cầu, dữ liệu, tính chất với các bài toán con
	
- Phân tích quá trình ra quyết định (RẤT QUAN TRỌNG)
    - Quyết định diễn ra ở đâu ?
	    - theo index?
	    - theo thời gian?
	    - theo số lượng đã chọn?

	- Mỗi quyết định ảnh hưởng **tương lai** như thế nào?
	- Để quyết định tiếp, **cần nhớ tối thiểu thông tin gì?**
    
👉 **Thông tin cần nhớ = mầm mống của state**

### _Nếu chưa có tiến triển_

-  Tìm một hướng khác dễ tiếp cận hơn
	- Suy nghĩ ngược lại
	- Tư duy theo 1 hướng khác
	- Nếu biết đáp án, thì có thể làm gì để suy ra điều đó không
-  Tim được các bài toán có liên quan, tương đồng, tổng quát, đặc biệt ? 
	 -  Có thể lấy 1 phần trong đó để giải không, cần thêm ẩn phụ không
- Giải 1 phần bài toán 
	- Giải bài toán nếu không có rằng buộc A hoặc B hoặc C...
		- Quan sát sự thay đổi của bài toán
	
## 3. Carry out the plan

### Chú ý : đây có thể là vòng lặp

- Xác định hướng đi của bài  toán :
	- Chiều thuận
	- Chiều ngược
	- Ưu tiên chiều thuận nếu cả 2 hướng có thể giải
- Định nghĩa state của DP dựa trên những điều trên
	- độ dài, tổng, số lượng, prefix, mex,....
- Dựa trên các rằng buộc, yêu cầu để chuyển state A sang state B
	- rằng buộc, yêu cầu cho ta biết ở state A có thể thực hiện các bước nào để sang state B
	- Nếu ta cố định 1 phần rằng buộc/dữ liệu/yêu cầu, có thể chuyển state không
	- khi sang state B cần những dữ kiện gì ở state A	
		- phát biểu lại state
		- thêm/bớt dữ kiện
- Lập công thức truy hồi khi đã xác định rõ ràng 3 điều trên
- Kiểm tra lại công thức
	- Chứng minh mỗi bước không trùng/thiếu state

### Nếu 1 trong 5 bước bị fail, quay về bước đầu tiên

## 4. Look back - nhìn lại bài toán

### _Can you derive the result differently? Can you improve it?_

Trong DP:

- State có dư không?
- Có thể giảm chiều?
- Có thể rolling array?
- Có thể đổi hướng duyệt?
- Có thể áp dụng phương pháp cho các dạng bài toán khác không

➡️ Đây là lúc từ **DP 3D → 2D → 1D**, hoặc từ O(N²) → O(N log N)
