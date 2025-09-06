## ✅ **Khi nào một bài toán binary selection có thể chuyển thành max flow / min cut?**

### 🔎 **Tiêu chí 1: Bài toán có thể biểu diễn dưới dạng Min Cut trong đồ thị có hướng**
> Nếu bạn có thể xây dựng một **đồ thị có hướng với source (s) và sink (t)**, sao cho:
> - Mỗi biến nhị phân \( x_i \in \{0,1\} \) tương ứng với việc **đỉnh \( i \) nằm ở phía source (chọn) hay sink (không chọn)**,
> - Chi phí của các lựa chọn và phụ thuộc được mã hóa bằng **trọng số cạnh**,
> - Thì bài toán tối ưu tương ứng với **tìm cắt nhỏ nhất (min s-t cut)**.

👉 **Dấu hiệu nhận biết**:  
Bạn có thể gán:
- Các lựa chọn tích cực → nối với **source**,
- Các lựa chọn tiêu cực → nối với **sink**,
- Các **phụ thuộc** hoặc **xung đột** → các cạnh giữa các đỉnh.

---

### 🔎 **Tiêu chí 2: Hàm mục tiêu có dạng submodular**
> Một hàm \( f: \{0,1\}^n \to \mathbb{R} \) là **submodular** nếu với mọi \( A \subseteq B \) và phần tử \( e \notin B \):
> \[
> f(A \cup \{e\}) - f(A) \ge f(B \cup \{e\}) - f(B)
> \]
> (hiệu ứng cận giảm dần)

Nhưng trong thực tế, ta thường xét **hàm phạt (penalty)** hoặc **chi phí** có dạng:

\[
\text{Minimize } \sum_i a_i x_i + \sum_{i,j} b_{ij} (x_i - x_j)^+
\]
hoặc
\[
\sum_i c_i [x_i = 0] + \sum_{i,j} d_{ij} [x_i = 1 \land x_j = 0]
\]

→ Đây là **dấu hiệu mạnh** rằng bài toán có thể chuyển sang min cut.

---

### 🔎 **Tiêu chí 3: Dạng tổng quát nhận diện được (Recognizable Form)**

Nếu bài toán của bạn có thể viết dưới dạng:

\[
\min_{x \in \{0,1\}^n} \left( \sum_{i} A_i x_i + \sum_{i} B_i (1 - x_i) + \sum_{(i,j) \in E} C_{ij} x_i (1 - x_j) \right)
\]

với \( A_i, B_i, C_{ij} \ge 0 \), thì **có thể chuyển thành min cut**.

> Giải thích:
> - \( A_i x_i \): phí nếu chọn \( i \)
> - \( B_i (1 - x_i) \): phí nếu không chọn \( i \)
> - \( C_{ij} x_i (1 - x_j) \): phí nếu chọn \( i \) nhưng không chọn \( j \) → thể hiện **phụ thuộc**: nếu chọn \( i \) thì phải chọn \( j \)

→ Tất cả đều là **tổn thất do xung đột hoặc vi phạm ràng buộc**, và có thể biểu diễn bằng cạnh trong đồ thị.

---

## 🧩 **Công thức nhận diện (Rule of Thumb)**

> ✅ **Một bài toán binary selection có thể chuyển thành max flow nếu nó có dạng:**

\[
\boxed{
\text{Minimize } \sum_{i \in S^+} p_i x_i + \sum_{i \in S^-} q_i (1 - x_i) + \sum_{(u,v) \in D} r_{uv} \cdot [x_u = 1 \land x_v = 0]
}
\quad \text{với } p_i, q_i, r_{uv} \ge 0
\]

Trong đó:
- \( x_i = 1 \): chọn phần tử \( i \),
- \( S^+ \): tập các phần tử bị phạt nếu **chọn**,
- \( S^- \): tập các phần tử bị phạt nếu **không chọn**,
- \( D \): tập các cặp \((u,v)\) mà nếu chọn \( u \) thì **phải chọn \( v \)**, nếu không sẽ bị phạt \( r_{uv} \).

👉 Đây là **dạng chuẩn** của bài toán có thể giải bằng **min cut**.

---

## 📌 Ví dụ minh họa: Image Segmentation

- Mỗi pixel \( i \): chọn \( x_i = 1 \) (foreground), \( x_i = 0 \) (background).
- Phạt \( a_i \) nếu gán sai: e.g. \( a_i \) nếu \( x_i = 1 \) (gán foreground cho pixel nên là background).
- Phạt \( b_{ij} \) nếu hai pixel kề nhau mà khác nhãn (để giữ biên mượt).

Hàm mục tiêu:
\[
\min \sum_i a_i (1 - x_i) + \sum_i b_i x_i + \sum_{(i,j)} w_{ij} |x_i - x_j|
\]

→ Có thể viết lại thành dạng submodular → chuyển sang min cut.

---

## 🚫 Khi nào KHÔNG thể chuyển?

| Dấu hiệu | Không thể dùng max flow |
|--------|--------------------------|
| Ràng buộc dạng \( \sum w_i x_i \le W \) (như Knapsack) | ❌ Không biểu diễn được bằng cắt |
| Hàm mục tiêu không submodular, có tương tác bậc cao | ❌ |
| Có ràng buộc toàn cục (ví dụ: chọn đúng k phần tử) | ❌ |
| Có chi phí tương tác âm (thưởng khi chọn cùng) | ⚠️ Chỉ một số trường hợp đặc biệt mới được |

> ⚠️ Lưu ý: Nếu có **thưởng khi chọn cùng** (reward for co-selection), thì hàm không còn submodular → không thể giải bằng min cut thông thường.

---

## ✅ Tóm lại: Công thức nhận diện

> **Một bài toán binary selection có thể chuyển thành max flow nếu:**

\[
\boxed{
\text{Chi phí tổng = (phí chọn) + (phí không chọn) + (phí vi phạm phụ thuộc)}
}
\]
và:
- Tất cả các phí đều **≥ 0**,
- Các phụ thuộc có dạng: "Nếu chọn A thì phải chọn B",
- Không có ràng buộc tổng (như trọng lượng, số lượng),
- Không có tương tác bậc cao hoặc thưởng.

👉 Khi đó, bạn có thể:
1. Tạo đỉnh cho mỗi phần tử,
2. Nối source → i với trọng số \( B_i \) (phí nếu không chọn),
3. Nối i → sink với trọng số \( A_i \) (phí nếu chọn),
4. Nối i → j với trọng số \( C_{ij} \) nếu chọn i phải chọn j.

→ **Min cut = giải pháp tối ưu**.
