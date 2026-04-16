#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct FastMCConfig {

    // =========================
    // Generator
    // =========================
    int idgen = 1;
    double p0 = 0, p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;
    std::string input_file = "";

    // =========================
    // Output
    // =========================
    std::string output_file = "output.root";

    // =========================
    // Event control
    // =========================
    int nevmax = 10000;
    int nevfreq = 100;
    int nevfrst = 0;

    // =========================
    // Geometry block (6 doubles each)
    // =========================
    std::vector<std::vector<double>> geometry;

    // =========================
    // Flags
    // =========================
    int div = 0;
    int ip = 0;
    int cross = 0;
    int fermi = 0;
    int frag = 0;
    int res = 0;
    int bckgrnd = 0;
    int nf = 0;
    int newreadout = 0;

    // =========================
    // Beam
    // =========================
    double theta_div = 0.0;
    double cross_angle = 0.0;

    struct IPBeam {
        double x = 0, dx = 0;
        double y = 0, dy = 0;
        double z = 0, dz = 0;
        int type = 0;
    } ipbeam;

    // =========================
    // Resolution
    // =========================
    double ZN[4] = {0};
    double ZP[4] = {0};

    // =========================
    // Readout
    // =========================
    double sigma_tof = 0.0;
    double baseline_mean = 0.0;
    double baseline_spread = 0.0;
};

inline void writeFastMC(const FastMCConfig& cfg, const std::string& filename = "fastmc.dat")
{
    std::ofstream f(filename);

    if (!f.is_open()) {
        std::cerr << "ERROR: cannot open " << filename << std::endl;
        return;
    }

    // =========================
    // 1. Generator
    // =========================
    f << cfg.idgen << " "
      << cfg.p0 << " " << cfg.p1 << " "
      << cfg.p2 << " " << cfg.p3 << " "
      << cfg.p4 << " " << cfg.p5 << "\n";

    if (std::abs(cfg.idgen) == 1 ||
        std::abs(cfg.idgen) == 2 ||
        std::abs(cfg.idgen) == 5)
    {
        f << cfg.input_file << "\n";
    }

    // =========================
    // 2. Output file
    // =========================
    f << cfg.output_file << "\n";

    // =========================
    // 3. Event control
    // =========================
    f << cfg.nevmax << " "
      << cfg.nevfreq << " "
      << cfg.nevfrst << "\n";

    // =========================
    // 4. Geometry
    // =========================
    for (const auto& g : cfg.geometry) {
        for (size_t i = 0; i < g.size(); i++) {
            f << g[i];
            if (i < g.size() - 1) f << " ";
        }
        f << "\n";
    }

    // =========================
    // 5. Flags
    // =========================
    f << cfg.div << " "
      << cfg.ip << " "
      << cfg.cross << " "
      << cfg.fermi << " "
      << cfg.frag << " "
      << cfg.res << " "
      << cfg.bckgrnd << " "
      << cfg.nf << " "
      << cfg.newreadout << "\n";

    // =========================
    // 6. Conditional blocks
    // =========================

    if (cfg.div != 0) {
        f << cfg.theta_div << "\n";
    }

    if (cfg.ip != 0) {
        f << cfg.ipbeam.x << " "
          << cfg.ipbeam.dx << " "
          << cfg.ipbeam.y << " "
          << cfg.ipbeam.dy << " "
          << cfg.ipbeam.z << " "
          << cfg.ipbeam.dz << " "
          << cfg.ipbeam.type << "\n";
    }

    if (cfg.cross != 0) {
        f << cfg.cross_angle << "\n";
    }

    if (cfg.res == 2) {
        f << cfg.ZN[0] << " " << cfg.ZN[1] << " "
          << cfg.ZN[2] << " " << cfg.ZN[3] << "\n";

        f << cfg.ZP[0] << " " << cfg.ZP[1] << " "
          << cfg.ZP[2] << " " << cfg.ZP[3] << "\n";
    }

    if (cfg.newreadout != 0) {
        if (std::abs(cfg.newreadout) == 1) {
            f << cfg.sigma_tof << "\n";
        }
        else if (std::abs(cfg.newreadout) == 2) {
            f << cfg.sigma_tof << " "
              << cfg.baseline_mean << " "
              << cfg.baseline_spread << "\n";
        }
    }

    f.close();

    std::cout << "✔ fastmc.dat generated: " << filename << std::endl;
}