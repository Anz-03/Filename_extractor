import os
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox

def browse_folder():
  """打开文件夹选择对话框，并将选择的文件夹路径显示在输入框中"""
  folder_path = filedialog.askdirectory()
  folder_path_entry.delete(0, tk.END)
  folder_path_entry.insert(0, folder_path)

def generate_file_list():
  """读取文件夹下所有文件名，并将它们写入txt文件"""
  folder_path = folder_path_entry.get()
  if not folder_path:
    messagebox.showerror("错误", "请选择文件夹！")
    return

  try:
    with open("file_list.txt", "w", encoding="utf-8") as f:
      for filename in os.listdir(folder_path):
        f.write(filename + "\n")
    messagebox.showinfo("成功", "文件列表已生成！")
  except Exception as e:
    messagebox.showerror("错误", f"发生错误：{e}")

# 创建主窗口
root = tk.Tk()
root.title("文件夹文件列表生成器")

# 文件夹路径输入框
folder_path_label = tk.Label(root, text="文件夹路径：")
folder_path_label.grid(row=0, column=0, padx=5, pady=5)
folder_path_entry = tk.Entry(root, width=50)
folder_path_entry.grid(row=0, column=1, padx=5, pady=5)

# 浏览按钮
browse_button = tk.Button(root, text="浏览", command=browse_folder)
browse_button.grid(row=0, column=2, padx=5, pady=5)

# 生成按钮
generate_button = tk.Button(root, text="生成文件列表", command=generate_file_list)
generate_button.grid(row=1, column=1, padx=5, pady=5)

root.mainloop()
