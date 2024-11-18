#include<iostream>
using namespace std;
//Khai báo Cấu trúc của danh sách liên kết
struct file{
	long long size;
	string addr;
	string name;
	long long time;//Giả sử thời gian tạo file theo kiểu long long 
	file* next;
};
// Khai báo ô nhớ D chứa danh sách file đứng đầu là head
struct listD{
	file* head;
};
//Khởi tạo giá trị của nốt đầu tiên = NULL
void D_document(listD* list){
	list->head = NULL;
}
//copy và chèn file
void insertFile(listD* list, long long size, string addr, string name, long long time){
	//Con trỏ *head đại diện cho file đầu tiên trong thư mục
	//Tạo 1 nốt mới để chèn dữ liệu của file cũ sang
	file* newfile = new file;
	newfile->size = size;
	newfile->addr = addr;
	newfile->name = name;
	newfile->time = time;
	newfile->next = NULL;
	//Tạo bản sao của con trỏ head
	file* head1 = list->head;
	//Trường hợp thư mục ban đầu rỗng
	if(list->head == NULL){
		list->head = newfile;
		return;
	}
	//Trường hợp thời gian của file chèn sang có trước file đầu tiên trong thư mục
	//Chèn vào đầu thư mục
	if(newfile->time < list->head->time){
		newfile->next = list->head;
		list->head = newfile;
		return;
	}
	//Trường hợp còn lại chèn vào giữa hoặc cuối
	else{
		//Chèn ở giữa
		while(head1->next != NULL){
			if(newfile->time >= head1->time && newfile->time <= head1->next->time){
				newfile->next = head1->next;
			    head1->next = newfile;
			    return;
			}
			head1 = head1->next;
		}
		//Nếu khong thỏa mãn ở giữa thì ta Chèn ở cuối
		if(head1->next == NULL){
			head1->next = newfile;
			newfile->next = NULL;
			return;
		}
	}
}
//Thực hiện tính toán kích thước các file trong thư mục
long long sum_size(listD* list){
	long long sum = 0;
	file* tmp = list->head;
	if(tmp == NULL) sum = 0;
	while(tmp != NULL){
		sum += tmp->size;
		tmp = tmp->next;
	}
	return sum;
}
//Thực hiện loại bỏ các file có dung lượng từ bé đến lớn đến khi bộ nhớ <= 32GB
//Đầu tiên tạo hàm swap để đổi dữ liệu giữa các nút
void swap(file* a, file* b) {
    if (a == nullptr || b == nullptr) return;
    // Hoán đổi kích thước
    int tempSize = a->size;
    a->size = b->size;
    b->size = tempSize;
    // Hoán đổi địa chỉ
    string tempAddr = a->addr;
    a->addr = b->addr;
    b->addr = tempAddr;
    // Hoán đổi tên file
    string tempName = a->name;
    a->name = b->name;
    b->name = tempName;
    // Hoán đổi thời gian
    long long tempTime = a->time;
    a->time = b->time;
    b->time = tempTime;
}
void deletefile(listD* list){
	const long long size_32GB = 1000; // giả sử 32gb bằng 1000kb ( 32GB số lớn quá :)))
	//Kiểm tra xem ổ nhớ có rỗng không?
	if(list->head == NULL) return;
	//Tiến hành tìm các file có size nhỏ nhất rồi loại bỏ dần
	//Sắp xếp các file theo thứ tự có size từ nhỏ đến lớn bằng thuật toán selectionsort
	for(file*i = list->head; i != NULL; i = i->next){
		file* min = i;
		for(file* j = i->next; j != NULL; j = j->next){
			if(min->size > j->size){
				min = j;
			}
		}
		swap(i, min);
	}
	// Tính tổng dung lượng ban đầu
    long long sum = sum_size(list);

    // Xóa dần các file từ đầu danh sách đến khi tổng dung lượng <= 32GB
    while (sum > size_32GB && list->head != NULL) {
        file* tmp = list->head;       // Lấy file đầu tiên (dung lượng nhỏ nhất sau khi sắp xếp)
        list->head = list->head->next; // Di chuyển con trỏ head sang file tiếp theo
        sum -= tmp->size;             // Trừ dung lượng của file vừa xóa khỏi tổng
        delete tmp;                   // Giải phóng bộ nhớ
    }
}
//in danh sách file trong bộ nhớ
void in(listD* list){
	file* temp = list->head;
	if(temp == NULL) cout<<"Khong co file nao ton tai";
	cout<<"Danh sach file trong bo nho la :"<<endl;
	while(temp != NULL){
		cout<<"size : "<<temp->size<<" | Dia chi : "<<temp->addr<<" | Ten : "<<temp->name<<" | Thoi gian : "<<temp->time<<endl;
		temp = temp->next;
	}
}
int main(){
	listD list;
	D_document(&list);
	insertFile(&list, 100, "D", "nguyen", 271);
	insertFile(&list, 200, "D", "minh", 259);
	insertFile(&list, 300, "D", "huong", 250);
	insertFile(&list, 400, "D", "dep", 282);
	insertFile(&list, 600, "D", "trai", 199);
	in(&list);
	cout<<"Tong dung luong cua o nho la: "<<sum_size(&list)<<endl;
	deletefile(&list);
	in(&list);
	return 0;
}
