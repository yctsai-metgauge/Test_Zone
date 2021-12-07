import sys
import pandas as pd


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('no argument')
        sys.exit()
    
    target_file = sys.argv[1]
    if (target_file[-4:]) != ".csv":
        target_file=target_file+".csv"
    print("Target file is: ",target_file)
    column_names = [i for i in range(0, 10)]
    df = pd.read_csv(target_file,sep=";",error_bad_lines=False,names=column_names)

    if df.iat[21,0]=='1':
        df_new = df.iloc[:, [2,3,4,5,6,7]]
        df_new = df_new.iloc[21:]
        print("file transform success")
        # df_new = df_new[df_new[7].notna()]
        file_name = target_file.find(".csv")
        target_file = target_file[:file_name] + "_mod" + ".csv"
        df_new.to_csv(target_file,sep=",",header=False, index=False)
        print("New file is: ",target_file)
    else:
        print("target_file format wrong")   

    