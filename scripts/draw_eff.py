import ROOT
import os
import numpy as np

# 设置ROOT样式
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
# ROOT.gStyle.SetPadTickX(1)
# ROOT.gStyle.SetPadTickY(1)
ROOT.gStyle.SetLegendBorderSize(0)
ROOT.gStyle.SetMarkerSize(1)

# 粒子颜色映射 - 使用更美观的颜色
particle_colors = {
    "poshadron": ROOT.kAzure+7,
    "neghadron": ROOT.kAzure+3,
    "pospion": ROOT.kRed+1,
    "negpion": ROOT.kRed-7,
    "proton": ROOT.kGreen+3,
    "antiproton": ROOT.kGreen-2,
    "lambda": ROOT.kOrange+7,
    "antilambda": ROOT.kOrange+1
}

# 粒子显示名称
particle_labels = {
    "poshadron": "h^{+}",
    "neghadron": "h^{-}",
    "pospion": "#pi^{+}",
    "negpion": "#pi^{-}",
    "proton": "p",
    "antiproton": "#bar{p}",
    "lambda": "#Lambda",
    "antilambda": "#bar{#Lambda}"
}

# 粒子标记样式
particle_markers = {
    "poshadron": 20,
    "neghadron": 24,
    "pospion": 21,
    "negpion": 25,
    "proton": 22,
    "antiproton": 26,
    "lambda": 23,
    "antilambda": 27
}

def create_plot_pad(pad, y_axis_title, pad_super_title, y_range=(0, 1.1)):
    pad.Clear()
    pad.cd()

    # 先绘制框架
    y_min, y_max = y_range
    frame = pad.DrawFrame(0, y_min, 5, y_max, y_axis_title)
    frame.GetXaxis().SetTitle("p_{T} (GeV/c)")
    frame.GetYaxis().SetTitle(y_axis_title)

    # 添加dataset信息到图中
    title = ROOT.TLatex()
    title.SetNDC()
    title.DrawLatex(0.2, 0.85, pad_super_title)
    title.SetTextAlign(22)

    # 最后创建图例
    legend = ROOT.TLegend(0.6, 0.65, 0.85, 0.85)
    legend.SetNColumns(2)
    legend.SetFillStyle(0)
    legend.SetBorderSize(0)

    return frame, legend, title

def draw_efficiency_plots(input_file, output_dir="plots"):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    f = ROOT.TFile.Open(input_file, "READ")
    if not f or f.IsZombie():
        print(f"无法打开文件: {input_file}")
        return

    datasets = ["18q", "18r"]
    particles = ["poshadron", "neghadron", "pospion", "negpion",
                 "proton", "antiproton", "lambda", "antilambda"]

    pad_titles = []

    # 效率图
    canvas_eff = ROOT.TCanvas("canvas_eff", "Particle Efficiencies", 1600, 700)
    canvas_eff.Divide(2, 1)

    for i, dataset in enumerate(datasets):
        # canvas_eff.cd(i + 1)
        # canvas_eff.GetPad(i + 1).SetLeftMargin(0.15)
        # canvas_eff.GetPad(i + 1).SetRightMargin(0.05)
        # canvas_eff.GetPad(i + 1).SetTopMargin(0.12)
        # canvas_eff.GetPad(i + 1).SetBottomMargin(0.15)

        frame_eff, legend_eff, p_title_eff = create_plot_pad(canvas_eff.GetPad(i + 1), "Efficiency", dataset)
        pad_titles.append(p_title_eff)

        for particle in particles:
            obj_name = f"eff_pt_{particle}_{dataset}"
            obj = f.Get(obj_name)

            if obj and obj.InheritsFrom("TEfficiency"):
                graph = obj.CreateGraph()
                color = particle_colors.get(particle, ROOT.kBlack)
                marker = particle_markers.get(particle, 20)
                graph.SetMarkerColor(color)
                graph.SetLineColor(color)
                graph.SetMarkerStyle(marker)
                graph.SetLineWidth(2)
                graph.Draw("PL SAME")
                legend_eff.AddEntry(graph, particle_labels.get(particle, particle), "pl")

        legend_eff.Draw()

    output_name_eff = f"{output_dir}/all_efficiencies_pt.pdf"
    canvas_eff.SaveAs(output_name_eff)
    print(f"已保存效率图: {output_name_eff}")

    # Ratio图
    canvas_ratio = ROOT.TCanvas("canvas_ratio", "Particle Ratios", 1600, 700)
    canvas_ratio.Divide(2, 1)

    for i, dataset in enumerate(datasets):
        canvas_ratio.cd(i + 1)
        # canvas_ratio.GetPad(i + 1).SetLeftMargin(0.15)
        # canvas_ratio.GetPad(i + 1).SetRightMargin(0.05)
        # canvas_ratio.GetPad(i + 1).SetTopMargin(0.12)
        # canvas_ratio.GetPad(i + 1).SetBottomMargin(0.15)

        frame_ratio, legend_ratio, p_title_ratio = create_plot_pad(canvas_ratio.GetPad(i + 1), "Ratio", dataset, (0.0, 1.0))
        pad_titles.append(p_title_ratio)

        for particle in particles:
            obj_name_graph = f"graph_ratio_pt_{particle}_{dataset}"
            obj = f.Get(obj_name_graph)

            if obj and obj.InheritsFrom("TGraphErrors"):
                color = particle_colors.get(particle, ROOT.kBlack)
                marker = particle_markers.get(particle, 20)
                obj.SetMarkerColor(color)
                obj.SetLineColor(color)
                obj.SetMarkerStyle(marker)
                obj.SetLineWidth(2)
                obj.Draw("PL SAME")
                legend_ratio.AddEntry(obj, particle_labels.get(particle, particle), "pl")

        legend_ratio.Draw()

    output_name_ratio = f"{output_dir}/all_ratios_pt.pdf"
    canvas_ratio.SaveAs(output_name_ratio)
    print(f"已保存Ratio图: {output_name_ratio}")

    f.Close()
    print("绘图完成!")

def main():
    input_file = "all_eff_pt.root"
    if not os.path.exists(input_file):
        print(f"错误: 文件 {input_file} 不存在!")
        print(f"请确保 '{input_file}' 在当前目录下或提供正确路径.")
        return

    output_dir = "efficiency_plots_pdf" # Changed output dir name slightly
    draw_efficiency_plots(input_file, output_dir)

if __name__ == "__main__":
    # Ensure ROOT can run in batch mode if no display is available
    ROOT.gROOT.SetBatch(True)
    main()
