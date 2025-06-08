import random
import string
code_type = ["var","if","if-else-if-else"]
strs = list(string.ascii_letters + "_")

def append_v(the_list, val):
    the_list.append(val)
    return val

def fake_code():
    code = "整数型 main(){\n整数型 ff = 0\n整数型 aa = 1\n"
    used_name = ["ff","aa"]
    for x in range(random.randint(5,20)):
        ctype = code_type[random.randint(0,2)]
        if ctype == "var":
            for x in range(random.randint(1,20)):
                code += "整数型 " + append_v(used_name,"".join([random.choice(strs) for x in range(random.randint(15,25))])) + " = 0\n"
        elif ctype == "if":
            #print("\033[31m",used_name,"\033[0m")
            code += f"如果({used_name[random.randint(2 if len(used_name) > 2 else 0,len(used_name) - 1)]} == {random.randint(5,20)}){{ff = 1}}\n"
            if random.randint(0,1) == 0:
                code += "否则{ff = 0}\n"
        else:
            code += f"如果({used_name[random.randint(2 if len(used_name) > 2 else 0,len(used_name) - 1)]} == {random.randint(5,20)}){{ff = 1}}\n"
            for x in range(random.randint(5,20)):
                code += f"否则 如果({used_name[random.randint(2 if len(used_name) > 2 else 0,len(used_name) - 1)]} == {random.randint(5,20)}){{ff = 1}}\n"
            if random.randint(0,1) == 0:
                code += "否则{ff = 0}\n"



    code += "返回 0;\n"
    code += "}\n"
    #print(used_name)
    return code

print(fake_code())

